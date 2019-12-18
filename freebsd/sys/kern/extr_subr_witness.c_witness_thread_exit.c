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
struct thread {struct lock_list_entry* td_sleeplocks; } ;
struct lock_list_entry {int ll_count; int /*<<< orphan*/ * ll_children; struct lock_list_entry* ll_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  kassert_panic (char*,struct thread*) ; 
 int /*<<< orphan*/ * panicstr ; 
 int /*<<< orphan*/  witness_list_lock (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (char*,struct thread*)) ; 
 int /*<<< orphan*/  witness_lock_list_free (struct lock_list_entry*) ; 
 int /*<<< orphan*/  witness_output (char*,struct thread*) ; 

void
witness_thread_exit(struct thread *td)
{
	struct lock_list_entry *lle;
	int i, n;

	lle = td->td_sleeplocks;
	if (lle == NULL || panicstr != NULL)
		return;
	if (lle->ll_count != 0) {
		for (n = 0; lle != NULL; lle = lle->ll_next)
			for (i = lle->ll_count - 1; i >= 0; i--) {
				if (n == 0)
					witness_output(
		    "Thread %p exiting with the following locks held:\n", td);
				n++;
				witness_list_lock(&lle->ll_children[i],
				    witness_output);
				
			}
		kassert_panic(
		    "Thread %p cannot exit while holding sleeplocks\n", td);
	}
	witness_lock_list_free(lle);
}