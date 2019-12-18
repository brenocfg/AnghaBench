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
typedef  int /*<<< orphan*/  zprop_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/ * zpool_prop_table ; 

zprop_desc_t *
zpool_prop_get_table(void)
{
	return (zpool_prop_table);
}