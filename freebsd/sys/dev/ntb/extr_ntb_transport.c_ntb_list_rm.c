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
 scalar_t__ STAILQ_EMPTY (struct ntb_queue_list*) ; 
 struct ntb_queue_entry* STAILQ_FIRST (struct ntb_queue_list*) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (struct ntb_queue_list*,struct ntb_queue_entry*) ; 
 int /*<<< orphan*/  mtx_lock_spin (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock_spin (struct mtx*) ; 

__attribute__((used)) static struct ntb_queue_entry *
ntb_list_rm(struct mtx *lock, struct ntb_queue_list *list)
{
	struct ntb_queue_entry *entry;

	mtx_lock_spin(lock);
	if (STAILQ_EMPTY(list)) {
		entry = NULL;
		goto out;
	}
	entry = STAILQ_FIRST(list);
	STAILQ_REMOVE_HEAD(list, entry);
out:
	mtx_unlock_spin(lock);

	return (entry);
}