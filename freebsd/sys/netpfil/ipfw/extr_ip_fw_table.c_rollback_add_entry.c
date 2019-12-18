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
struct tableop_state {void* tc; void* ch; int modified; } ;
struct op_state {int dummy; } ;
typedef  void ip_fw_chain ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_UH_WLOCK_ASSERT (void*) ; 
 int /*<<< orphan*/  rollback_table_values (struct tableop_state*) ; 

__attribute__((used)) static void
rollback_add_entry(void *object, struct op_state *_state)
{
	struct ip_fw_chain *ch;
	struct tableop_state *ts;

	ts = (struct tableop_state *)_state;

	if (ts->tc != object && ts->ch != object)
		return;

	ch = ts->ch;

	IPFW_UH_WLOCK_ASSERT(ch);

	/* Call specifid unlockers */
	rollback_table_values(ts);

	/* Indicate we've called */
	ts->modified = 1;
}