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
typedef  char wchar_t ;

/* Variables and functions */
 int INT_MAX ; 

__attribute__((used)) static int
isint_w(const wchar_t *start, const wchar_t *end, int *result)
{
	int n = 0;
	if (start >= end)
		return (0);
	while (start < end) {
		if (*start < '0' || *start > '9')
			return (0);
		if (n > (INT_MAX / 10) ||
		    (n == INT_MAX / 10 && (*start - '0') > INT_MAX % 10)) {
			n = INT_MAX;
		} else {
			n *= 10;
			n += *start - '0';
		}
		start++;
	}
	*result = n;
	return (1);
}