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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  bit_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bit_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int nitems (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * proc_id_array ; 
 int /*<<< orphan*/  procid_lock ; 

void
proc_id_set_cond(int type, pid_t id)
{

	KASSERT(type >= 0 && type < nitems(proc_id_array),
	    ("invalid type %d\n", type));
	if (bit_test(proc_id_array[type], id))
		return;
	mtx_lock(&procid_lock);
	bit_set(proc_id_array[type], id);
	mtx_unlock(&procid_lock);
}