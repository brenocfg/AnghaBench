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
typedef  int krb5_flags ;

/* Variables and functions */
 int /*<<< orphan*/  kdb_attrs ; 
 int parse_flags (char const*,int /*<<< orphan*/ ,int) ; 

int
str2attributes(const char *str, krb5_flags *flags)
{
    int res;

    res = parse_flags (str, kdb_attrs, *flags);
    if (res < 0)
	return res;
    else {
	*flags = res;
	return 0;
    }
}