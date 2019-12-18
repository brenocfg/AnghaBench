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
struct lock_list_entry {struct lock_list_entry* ll_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 struct lock_list_entry* w_lock_list_free ; 
 int /*<<< orphan*/  w_mtx ; 

__attribute__((used)) static void
witness_lock_list_free(struct lock_list_entry *lle)
{

	mtx_lock_spin(&w_mtx);
	lle->ll_next = w_lock_list_free;
	w_lock_list_free = lle;
	mtx_unlock_spin(&w_mtx);
}