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
typedef  scalar_t__ rsize_t ;

/* Variables and functions */
 int /*<<< orphan*/  E2BIG ; 
 int EOF ; 
 int /*<<< orphan*/  ORIENT (int /*<<< orphan*/ ,int) ; 
 int __sgetc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __throw_constraint_handler_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 

__attribute__((used)) static inline char *
_gets_s(char *buf, rsize_t n)
{
	int c;
	char *s;

	ORIENT(stdin, -1);
	for (s = buf, n--; (c = __sgetc(stdin)) != '\n' && n > 0 ; n--) {
		if (c == EOF) {
			if (s == buf) {
				return (NULL);
			} else
				break;
		} else
			*s++ = c;
	}

	/*
 	 * If end of buffer reached, discard until \n or eof.
	 * Then throw an error.
	 */
	if (n == 0) {
		/* discard */
		while ((c = __sgetc(stdin)) != '\n' && c != EOF);
		/* throw the error after lock released prior to exit */
		__throw_constraint_handler_s("gets_s : end of buffer", E2BIG);
		return (NULL);
	}
	*s = 0;
	return (buf);
}