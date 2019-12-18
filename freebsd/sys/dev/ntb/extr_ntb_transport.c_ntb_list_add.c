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
struct ntb_queue_list {int dummy; } ;
struct ntb_queue_entry {int dummy; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (struct ntb_queue_list*,struct ntb_queue_entry*,struct ntb_queue_entry*) ; 
 int /*<<< orphan*/  mtx_lock_spin (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock_spin (struct mtx*) ; 

__attribute__((used)) static void
ntb_list_add(struct mtx *lock, struct ntb_queue_entry *entry,
    struct ntb_queue_list *list)
{

	mtx_lock_spin(lock);
	STAILQ_INSERT_TAIL(list, entry, entry);
	mtx_unlock_spin(lock);
}