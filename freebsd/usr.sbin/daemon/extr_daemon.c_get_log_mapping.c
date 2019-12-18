#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int c_val; scalar_t__ c_name; } ;
typedef  TYPE_1__ CODE ;

/* Variables and functions */
 scalar_t__ strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static int
get_log_mapping(const char *str, const CODE *c)
{
	const CODE *cp;
	for (cp = c; cp->c_name; cp++)
		if (strcmp(cp->c_name, str) == 0)
			return cp->c_val;
	return -1;
}