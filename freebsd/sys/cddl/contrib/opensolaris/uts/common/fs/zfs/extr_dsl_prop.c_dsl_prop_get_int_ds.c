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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int dsl_prop_get_ds (int /*<<< orphan*/ *,char const*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
dsl_prop_get_int_ds(dsl_dataset_t *ds, const char *propname,
    uint64_t *valuep)
{
	return (dsl_prop_get_ds(ds, propname, 8, 1, valuep, NULL));
}