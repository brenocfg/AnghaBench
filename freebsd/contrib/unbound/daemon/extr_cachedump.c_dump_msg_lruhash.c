#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * now; } ;
struct worker {TYPE_1__ env; int /*<<< orphan*/  scratchpad; } ;
struct reply_info {int dummy; } ;
struct query_info {int dummy; } ;
struct lruhash_entry {int /*<<< orphan*/  lock; struct lruhash_entry* lru_next; } ;
struct lruhash {struct lruhash_entry* lru_start; } ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  copy_msg (int /*<<< orphan*/ ,struct lruhash_entry*,struct query_info**,struct reply_info**) ; 
 int /*<<< orphan*/  dump_msg (int /*<<< orphan*/ *,struct query_info*,struct reply_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regional_free_all (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dump_msg_lruhash(RES* ssl, struct worker* worker, struct lruhash* h)
{
	struct lruhash_entry* e;
	struct query_info* k;
	struct reply_info* d;

	/* lruhash already locked by caller */
	/* walk in order of lru; best first */
	for(e=h->lru_start; e; e = e->lru_next) {
		regional_free_all(worker->scratchpad);
		lock_rw_rdlock(&e->lock);
		/* make copy of rrset in worker buffer */
		if(!copy_msg(worker->scratchpad, e, &k, &d)) {
			lock_rw_unlock(&e->lock);
			return 0;
		}
		lock_rw_unlock(&e->lock);
		/* release lock so we can lookup the rrset references 
		 * in the rrset cache */
		if(!dump_msg(ssl, k, d, *worker->env.now)) {
			return 0;
		}
	}
	return 1;
}