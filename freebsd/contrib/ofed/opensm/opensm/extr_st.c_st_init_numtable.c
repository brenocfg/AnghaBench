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
typedef  int /*<<< orphan*/  st_table ;

/* Variables and functions */
 int /*<<< orphan*/ * st_init_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  type_numhash ; 

st_table *st_init_numtable(void)
{
	return st_init_table(&type_numhash);
}