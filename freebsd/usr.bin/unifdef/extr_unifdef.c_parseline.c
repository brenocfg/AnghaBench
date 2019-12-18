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
typedef  scalar_t__ Linetype ;
typedef  size_t Comment_state ;

/* Variables and functions */
 int /*<<< orphan*/  Eioccc () ; 
 size_t LS_DIRTY ; 
 size_t LS_HASH ; 
 size_t LS_START ; 
 scalar_t__ LT_ELFALSE ; 
 scalar_t__ LT_ELIF ; 
 scalar_t__ LT_ELSE ; 
 scalar_t__ LT_ELTRUE ; 
 scalar_t__ LT_ENDIF ; 
 scalar_t__ LT_EOF ; 
 scalar_t__ LT_FALSE ; 
 scalar_t__ LT_FALSEI ; 
 scalar_t__ LT_IF ; 
 scalar_t__ LT_PLAIN ; 
 scalar_t__ LT_TRUE ; 
 scalar_t__ LT_TRUEI ; 
 scalar_t__ MAXLINE ; 
 int /*<<< orphan*/ * comment_name ; 
 int /*<<< orphan*/  debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char const*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filename ; 
 int findsym (char const**) ; 
 scalar_t__ ifeval (char const**) ; 
 scalar_t__* ignore ; 
 size_t incomment ; 
 int /*<<< orphan*/  input ; 
 char* keyword ; 
 int /*<<< orphan*/  linenum ; 
 size_t linestate ; 
 int /*<<< orphan*/ * linestate_name ; 
 scalar_t__ linetype_2dodgy (scalar_t__) ; 
 scalar_t__ linetype_if2elif (scalar_t__) ; 
 char* matchsym (char*,char*) ; 
 int /*<<< orphan*/ * newline ; 
 int /*<<< orphan*/ * newline_crlf ; 
 int /*<<< orphan*/ * newline_unix ; 
 char* skipcomment (char const*) ; 
 char* skiphash () ; 
 char* skipline (char const*) ; 
 char* skipsym (char*) ; 
 int /*<<< orphan*/  strcpy (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 scalar_t__ strrchr (char const*,char) ; 
 char const* tline ; 
 int /*<<< orphan*/ ** value ; 

__attribute__((used)) static Linetype
parseline(void)
{
	const char *cp;
	int cursym;
	Linetype retval;
	Comment_state wascomment;

	wascomment = incomment;
	cp = skiphash();
	if (cp == NULL)
		return (LT_EOF);
	if (newline == NULL) {
		if (strrchr(tline, '\n') == strrchr(tline, '\r') + 1)
			newline = newline_crlf;
		else
			newline = newline_unix;
	}
	if (*cp == '\0') {
		retval = LT_PLAIN;
		goto done;
	}
	keyword = tline + (cp - tline);
	if ((cp = matchsym("ifdef", keyword)) != NULL ||
	    (cp = matchsym("ifndef", keyword)) != NULL) {
		cp = skipcomment(cp);
		if ((cursym = findsym(&cp)) < 0)
			retval = LT_IF;
		else {
			retval = (keyword[2] == 'n')
			    ? LT_FALSE : LT_TRUE;
			if (value[cursym] == NULL)
				retval = (retval == LT_TRUE)
				    ? LT_FALSE : LT_TRUE;
			if (ignore[cursym])
				retval = (retval == LT_TRUE)
				    ? LT_TRUEI : LT_FALSEI;
		}
	} else if ((cp = matchsym("if", keyword)) != NULL)
		retval = ifeval(&cp);
	else if ((cp = matchsym("elif", keyword)) != NULL)
		retval = linetype_if2elif(ifeval(&cp));
	else if ((cp = matchsym("else", keyword)) != NULL)
		retval = LT_ELSE;
	else if ((cp = matchsym("endif", keyword)) != NULL)
		retval = LT_ENDIF;
	else {
		cp = skipsym(keyword);
		/* no way can we deal with a continuation inside a keyword */
		if (strncmp(cp, "\\\r\n", 3) == 0 ||
		    strncmp(cp, "\\\n", 2) == 0)
			Eioccc();
		cp = skipline(cp);
		retval = LT_PLAIN;
		goto done;
	}
	cp = skipcomment(cp);
	if (*cp != '\0') {
		cp = skipline(cp);
		if (retval == LT_TRUE || retval == LT_FALSE ||
		    retval == LT_TRUEI || retval == LT_FALSEI)
			retval = LT_IF;
		if (retval == LT_ELTRUE || retval == LT_ELFALSE)
			retval = LT_ELIF;
	}
	/* the following can happen if the last line of the file lacks a
	   newline or if there is too much whitespace in a directive */
	if (linestate == LS_HASH) {
		long len = cp - tline;
		if (fgets(tline + len, MAXLINE - len, input) == NULL) {
			if (ferror(input))
				err(2, "can't read %s", filename);
			/* append the missing newline at eof */
			strcpy(tline + len, newline);
			cp += strlen(newline);
			linestate = LS_START;
		} else {
			linestate = LS_DIRTY;
		}
	}
	if (retval != LT_PLAIN && (wascomment || linestate != LS_START)) {
		retval = linetype_2dodgy(retval);
		linestate = LS_DIRTY;
	}
done:
	debug("parser line %d state %s comment %s line", linenum,
	    comment_name[incomment], linestate_name[linestate]);
	return (retval);
}