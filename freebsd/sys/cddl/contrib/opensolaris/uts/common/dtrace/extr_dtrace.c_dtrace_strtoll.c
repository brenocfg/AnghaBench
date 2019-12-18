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
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int DIGIT (char) ; 
 char dtrace_load8 (uintptr_t) ; 
 scalar_t__ isxdigit (char) ; 
 scalar_t__ lisalnum (char) ; 

__attribute__((used)) static int64_t
dtrace_strtoll(char *input, int base, size_t limit)
{
	uintptr_t pos = (uintptr_t)input;
	int64_t val = 0;
	int x;
	boolean_t neg = B_FALSE;
	char c, cc, ccc;
	uintptr_t end = pos + limit;

	/*
	 * Consume any whitespace preceding digits.
	 */
	while ((c = dtrace_load8(pos)) == ' ' || c == '\t')
		pos++;

	/*
	 * Handle an explicit sign if one is present.
	 */
	if (c == '-' || c == '+') {
		if (c == '-')
			neg = B_TRUE;
		c = dtrace_load8(++pos);
	}

	/*
	 * Check for an explicit hexadecimal prefix ("0x" or "0X") and skip it
	 * if present.
	 */
	if (base == 16 && c == '0' && ((cc = dtrace_load8(pos + 1)) == 'x' ||
	    cc == 'X') && isxdigit(ccc = dtrace_load8(pos + 2))) {
		pos += 2;
		c = ccc;
	}

	/*
	 * Read in contiguous digits until the first non-digit character.
	 */
	for (; pos < end && c != '\0' && lisalnum(c) && (x = DIGIT(c)) < base;
	    c = dtrace_load8(++pos))
		val = val * base + x;

	return (neg ? -val : val);
}