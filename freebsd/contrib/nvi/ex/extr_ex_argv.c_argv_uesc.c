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
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  EXCMD ;
typedef  char CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  GET_SPACE_GOTOW (int /*<<< orphan*/ *,char*,size_t,size_t) ; 
 scalar_t__ IS_ESCAPE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char) ; 

CHAR_T *
argv_uesc(SCR *sp, EXCMD *excp, CHAR_T *str, size_t len)
{
	size_t blen;
	CHAR_T *bp, *p;

	GET_SPACE_GOTOW(sp, bp, blen, len + 1);

	for (p = bp; len > 0; ++str, --len) {
		if (IS_ESCAPE(sp, excp, *str)) {
			if (--len < 1)
				break;
			++str;
		} else if (*str == '\\') {
			if (--len < 1)
				break;
			++str;

			/* Check for double escaping. */
			if (*str == '\\' && len > 1)
				switch (str[1]) {
				case '!': case '%': case '#':
					++str;
					--len;
				}
		}
		*p++ = *str;
	}
	*p = '\0';

	return bp;

alloc_err:
	return NULL;
}