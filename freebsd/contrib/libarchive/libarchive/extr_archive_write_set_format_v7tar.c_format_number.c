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
typedef  int int64_t ;

/* Variables and functions */
 int format_256 (int,char*,int) ; 
 int format_octal (int,char*,int) ; 

__attribute__((used)) static int
format_number(int64_t v, char *p, int s, int maxsize, int strict)
{
	int64_t limit;

	limit = ((int64_t)1 << (s*3));

	/* "Strict" only permits octal values with proper termination. */
	if (strict)
		return (format_octal(v, p, s));

	/*
	 * In non-strict mode, we allow the number to overwrite one or
	 * more bytes of the field termination.  Even old tar
	 * implementations should be able to handle this with no
	 * problem.
	 */
	if (v >= 0) {
		while (s <= maxsize) {
			if (v < limit)
				return (format_octal(v, p, s));
			s++;
			limit <<= 3;
		}
	}

	/* Base-256 can handle any number, positive or negative. */
	return (format_256(v, p, maxsize));
}