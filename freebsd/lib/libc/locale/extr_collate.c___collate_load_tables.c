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
 int __collate_load_tables_l (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __xlocale_global_collate ; 

int
__collate_load_tables(const char *encoding)
{

	return (__collate_load_tables_l(encoding, &__xlocale_global_collate));
}