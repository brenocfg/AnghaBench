#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  char uschar ;
struct charclass {int /*<<< orphan*/  (* cc_func ) (int) ;int /*<<< orphan*/  cc_namelen; int /*<<< orphan*/ * cc_name; } ;

/* Variables and functions */
 int CCL ; 
 int CHAR ; 
 int DOT ; 
 int EMPTYRE ; 
 int /*<<< orphan*/  FATAL (char*,int /*<<< orphan*/ ) ; 
 int NCCL ; 
 int OR ; 
 int PLUS ; 
 int QUEST ; 
 int STAR ; 
 int UCHAR_MAX ; 
 int /*<<< orphan*/  adjbuf (char**,int*,int,int,char**,char*) ; 
 struct charclass* charclasses ; 
 int /*<<< orphan*/  isdigit (int) ; 
 int /*<<< orphan*/  lastatom ; 
 int /*<<< orphan*/  lastre ; 
 scalar_t__ malloc (int) ; 
 char* prestr ; 
 char quoted (char**) ; 
 int /*<<< orphan*/  repeat (char*,char*,int /*<<< orphan*/ ,char const*,int,int) ; 
 char* rlxstr ; 
 char rlxval ; 
 char* starttok ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 scalar_t__ tostring (char*) ; 

int relex(void)		/* lexical analyzer for reparse */
{
	int c, n;
	int cflag;
	static uschar *buf = NULL;
	static int bufsz = 100;
	uschar *bp;
	struct charclass *cc;
	int i;
	int num, m, commafound, digitfound;
	const uschar *startreptok;

rescan:
	starttok = prestr;

	switch (c = *prestr++) {
	case '|': return OR;
	case '*': return STAR;
	case '+': return PLUS;
	case '?': return QUEST;
	case '.': return DOT;
	case '\0': prestr--; return '\0';
	case '^':
	case '$':
	case '(':
	case ')':
		return c;
	case '\\':
		rlxval = quoted(&prestr);
		return CHAR;
	default:
		rlxval = c;
		return CHAR;
	case '[': 
		if (buf == NULL && (buf = (uschar *) malloc(bufsz)) == NULL)
			FATAL("out of space in reg expr %.10s..", lastre);
		bp = buf;
		if (*prestr == '^') {
			cflag = 1;
			prestr++;
		}
		else
			cflag = 0;
		n = 2 * strlen((const char *) prestr)+1;
		if (!adjbuf((char **) &buf, &bufsz, n, n, (char **) &bp, "relex1"))
			FATAL("out of space for reg expr %.10s...", lastre);
		for (; ; ) {
			if ((c = *prestr++) == '\\') {
				*bp++ = '\\';
				if ((c = *prestr++) == '\0')
					FATAL("nonterminated character class %.20s...", lastre);
				*bp++ = c;
			/* } else if (c == '\n') { */
			/* 	FATAL("newline in character class %.20s...", lastre); */
			} else if (c == '[' && *prestr == ':') {
				/* POSIX char class names, Dag-Erling Smorgrav, des@ofug.org */
				for (cc = charclasses; cc->cc_name; cc++)
					if (strncmp((const char *) prestr + 1, (const char *) cc->cc_name, cc->cc_namelen) == 0)
						break;
				if (cc->cc_name != NULL && prestr[1 + cc->cc_namelen] == ':' &&
				    prestr[2 + cc->cc_namelen] == ']') {
					prestr += cc->cc_namelen + 3;
					/*
					 * BUG: We begin at 1, instead of 0, since we
					 * would otherwise prematurely terminate the
					 * string for classes like [[:cntrl:]]. This
					 * means that we can't match the NUL character,
					 * not without first adapting the entire
					 * program to track each string's length.
					 */
					for (i = 1; i <= UCHAR_MAX; i++) {
						if (!adjbuf((char **) &buf, &bufsz, bp-buf+1, 100, (char **) &bp, "relex2"))
						    FATAL("out of space for reg expr %.10s...", lastre);
						if (cc->cc_func(i)) {
							*bp++ = i;
							n++;
						}
					}
				} else
					*bp++ = c;
			} else if (c == '[' && *prestr == '.') {
				char collate_char;
				prestr++;
				collate_char = *prestr++;
				if (*prestr == '.' && prestr[1] == ']') {
					prestr += 2;
					/* Found it: map via locale TBD: for
					   now, simply return this char.  This
					   is sufficient to pass conformance
					   test awk.ex 156
					 */
					if (*prestr == ']') {
						prestr++;
						rlxval = collate_char;
						return CHAR;
					}
				}
			} else if (c == '[' && *prestr == '=') {
				char equiv_char;
				prestr++;
				equiv_char = *prestr++;
				if (*prestr == '=' && prestr[1] == ']') {
					prestr += 2;
					/* Found it: map via locale TBD: for now
					   simply return this char. This is
					   sufficient to pass conformance test
					   awk.ex 156
					 */
					if (*prestr == ']') {
						prestr++;
						rlxval = equiv_char;
						return CHAR;
					}
				}
			} else if (c == '\0') {
				FATAL("nonterminated character class %.20s", lastre);
			} else if (bp == buf) {	/* 1st char is special */
				*bp++ = c;
			} else if (c == ']') {
				*bp++ = 0;
				rlxstr = (uschar *) tostring((char *) buf);
				if (cflag == 0)
					return CCL;
				else
					return NCCL;
			} else
				*bp++ = c;
		}
		break;
	case '{':
		if (isdigit(*(prestr))) {
			num = 0;	/* Process as a repetition */
			n = -1; m = -1;
			commafound = 0;
			digitfound = 0;
			startreptok = prestr-1;
			/* Remember start of previous atom here ? */
		} else {        	/* just a { char, not a repetition */
			rlxval = c;
			return CHAR;
                }
		for (; ; ) {
			if ((c = *prestr++) == '}') {
				if (commafound) {
					if (digitfound) { /* {n,m} */
						m = num;
						if (m<n)
							FATAL("illegal repetition expression: class %.20s",
								lastre);
						if ((n==0) && (m==1)) {
							return QUEST;
						}
					} else {	/* {n,} */
						if (n==0) return STAR;
						if (n==1) return PLUS;
					}
				} else {
					if (digitfound) { /* {n} same as {n,n} */
						n = num;
						m = num;
					} else {	/* {} */
						FATAL("illegal repetition expression: class %.20s",
							lastre);
					}
				}
				if (repeat(starttok, prestr-starttok, lastatom,
					   startreptok - lastatom, n, m) > 0) {
					if ((n==0) && (m==0)) {
						return EMPTYRE;
					}
					/* must rescan input for next token */
					goto rescan;
				}
				/* Failed to replace: eat up {...} characters
				   and treat like just PLUS */
				return PLUS;
			} else if (c == '\0') {
				FATAL("nonterminated character class %.20s",
					lastre);
			} else if (isdigit(c)) {
				num = 10 * num + c - '0';
				digitfound = 1;
			} else if (c == ',') {
				if (commafound)
					FATAL("illegal repetition expression: class %.20s",
						lastre);
				/* looking for {n,} or {n,m} */
				commafound = 1;
				n = num;
				digitfound = 0; /* reset */
				num = 0;
			} else {
				FATAL("illegal repetition expression: class %.20s",
					lastre);
			}
		}
		break;
	}
}