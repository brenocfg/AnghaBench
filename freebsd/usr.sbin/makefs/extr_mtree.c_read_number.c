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
typedef  int /*<<< orphan*/  u_int ;
typedef  scalar_t__ intmax_t ;

/* Variables and functions */
 int EDOM ; 
 int EINVAL ; 
 scalar_t__ strtoimax (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
read_number(const char *tok, u_int base, intmax_t *res, intmax_t min,
    intmax_t max)
{
	char *end;
	intmax_t val;

	val = strtoimax(tok, &end, base);
	if (end == tok || end[0] != '\0')
		return (EINVAL);
	if (val < min || val > max)
		return (EDOM);
	*res = val;
	return (0);
}