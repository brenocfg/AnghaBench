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

/* Variables and functions */
 int snprintf (char*,size_t,char*,int,char const*,char*,char*) ; 

__attribute__((used)) static int
print_unit (char *s, size_t len, int divisor, const char *name, int rem)
{
    return snprintf (s, len, "%u %s%s%s",
		     divisor, name,
		     divisor == 1 ? "" : "s",
		     rem > 0 ? " " : "");
}