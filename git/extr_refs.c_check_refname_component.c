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
struct strbuf {size_t len; char* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_SUFFIX ; 
 int LOCK_SUFFIX_LEN ; 
 int REFNAME_REFSPEC_PATTERN ; 
 int /*<<< orphan*/  memcmp (char const*,int /*<<< orphan*/ ,int) ; 
 unsigned char* refname_disposition ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 scalar_t__ strbuf_strip_suffix (struct strbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_refname_component(const char *refname, int *flags,
				   struct strbuf *sanitized)
{
	const char *cp;
	char last = '\0';
	size_t component_start = 0; /* garbage - not a reasonable initial value */

	if (sanitized)
		component_start = sanitized->len;

	for (cp = refname; ; cp++) {
		int ch = *cp & 255;
		unsigned char disp = refname_disposition[ch];

		if (sanitized && disp != 1)
			strbuf_addch(sanitized, ch);

		switch (disp) {
		case 1:
			goto out;
		case 2:
			if (last == '.') { /* Refname contains "..". */
				if (sanitized)
					/* collapse ".." to single "." */
					strbuf_setlen(sanitized, sanitized->len - 1);
				else
					return -1;
			}
			break;
		case 3:
			if (last == '@') { /* Refname contains "@{". */
				if (sanitized)
					sanitized->buf[sanitized->len-1] = '-';
				else
					return -1;
			}
			break;
		case 4:
			/* forbidden char */
			if (sanitized)
				sanitized->buf[sanitized->len-1] = '-';
			else
				return -1;
			break;
		case 5:
			if (!(*flags & REFNAME_REFSPEC_PATTERN)) {
				/* refspec can't be a pattern */
				if (sanitized)
					sanitized->buf[sanitized->len-1] = '-';
				else
					return -1;
			}

			/*
			 * Unset the pattern flag so that we only accept
			 * a single asterisk for one side of refspec.
			 */
			*flags &= ~ REFNAME_REFSPEC_PATTERN;
			break;
		}
		last = ch;
	}
out:
	if (cp == refname)
		return 0; /* Component has zero length. */

	if (refname[0] == '.') { /* Component starts with '.'. */
		if (sanitized)
			sanitized->buf[component_start] = '-';
		else
			return -1;
	}
	if (cp - refname >= LOCK_SUFFIX_LEN &&
	    !memcmp(cp - LOCK_SUFFIX_LEN, LOCK_SUFFIX, LOCK_SUFFIX_LEN)) {
		if (!sanitized)
			return -1;
		/* Refname ends with ".lock". */
		while (strbuf_strip_suffix(sanitized, LOCK_SUFFIX)) {
			/* try again in case we have .lock.lock */
		}
	}
	return cp - refname;
}