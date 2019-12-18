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
typedef  scalar_t__ u_int ;
typedef  char u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_TTEST (char const) ; 
 int /*<<< orphan*/  isascii (char const) ; 
 int /*<<< orphan*/  isprint (char const) ; 
 scalar_t__ isspace (char const) ; 

__attribute__((used)) static int
fetch_token(netdissect_options *ndo, const u_char *pptr, u_int idx, u_int len,
    u_char *tbuf, size_t tbuflen)
{
	size_t toklen = 0;

	for (; idx < len; idx++) {
		if (!ND_TTEST(*(pptr + idx))) {
			/* ran past end of captured data */
			return (0);
		}
		if (!isascii(*(pptr + idx))) {
			/* not an ASCII character */
			return (0);
		}
		if (isspace(*(pptr + idx))) {
			/* end of token */
			break;
		}
		if (!isprint(*(pptr + idx))) {
			/* not part of a command token or response code */
			return (0);
		}
		if (toklen + 2 > tbuflen) {
			/* no room for this character and terminating '\0' */
			return (0);
		}
		tbuf[toklen] = *(pptr + idx);
		toklen++;
	}
	if (toklen == 0) {
		/* no token */
		return (0);
	}
	tbuf[toklen] = '\0';

	/*
	 * Skip past any white space after the token, until we see
	 * an end-of-line (CR or LF).
	 */
	for (; idx < len; idx++) {
		if (!ND_TTEST(*(pptr + idx))) {
			/* ran past end of captured data */
			break;
		}
		if (*(pptr + idx) == '\r' || *(pptr + idx) == '\n') {
			/* end of line */
			break;
		}
		if (!isascii(*(pptr + idx)) || !isprint(*(pptr + idx))) {
			/* not a printable ASCII character */
			break;
		}
		if (!isspace(*(pptr + idx))) {
			/* beginning of next token */
			break;
		}
	}
	return (idx);
}