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
typedef  int /*<<< orphan*/  objset_used_cb_t ;
typedef  size_t dmu_objset_type_t ;

/* Variables and functions */
 int /*<<< orphan*/ ** used_cbs ; 

void
dmu_objset_register_type(dmu_objset_type_t ost, objset_used_cb_t *cb)
{
	used_cbs[ost] = cb;
}