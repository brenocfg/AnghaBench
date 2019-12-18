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
struct TYPE_2__ {int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int LOCK_OWNER_HASH_SIZE ; 
 int /*<<< orphan*/  graph_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* lf_lock_owners ; 
 int /*<<< orphan*/  lf_lock_states ; 
 int /*<<< orphan*/  lf_lock_states_lock ; 
 int /*<<< orphan*/  lf_owner_graph ; 
 int /*<<< orphan*/  lf_owner_graph_lock ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
lf_init(void *dummy)
{
	int i;

	sx_init(&lf_lock_states_lock, "lock states lock");
	LIST_INIT(&lf_lock_states);

	for (i = 0; i < LOCK_OWNER_HASH_SIZE; i++) {
		sx_init(&lf_lock_owners[i].lock, "lock owners lock");
		LIST_INIT(&lf_lock_owners[i].list);
	}

	sx_init(&lf_owner_graph_lock, "owner graph lock");
	graph_init(&lf_owner_graph);
}