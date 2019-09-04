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
struct TYPE_2__ {int /*<<< orphan*/  compare; } ;
struct negotiation_state {TYPE_1__ rev_list; } ;
struct fetch_negotiator {struct negotiation_state* data; int /*<<< orphan*/  release; int /*<<< orphan*/  ack; int /*<<< orphan*/  next; int /*<<< orphan*/  add_tip; int /*<<< orphan*/  known_common; } ;

/* Variables and functions */
 int /*<<< orphan*/  ack ; 
 int /*<<< orphan*/  add_tip ; 
 int /*<<< orphan*/  clear_marks ; 
 int /*<<< orphan*/  compare_commits_by_commit_date ; 
 int /*<<< orphan*/  for_each_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  known_common ; 
 int marked ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  release ; 
 struct negotiation_state* xcalloc (int,int) ; 

void default_negotiator_init(struct fetch_negotiator *negotiator)
{
	struct negotiation_state *ns;
	negotiator->known_common = known_common;
	negotiator->add_tip = add_tip;
	negotiator->next = next;
	negotiator->ack = ack;
	negotiator->release = release;
	negotiator->data = ns = xcalloc(1, sizeof(*ns));
	ns->rev_list.compare = compare_commits_by_commit_date;

	if (marked)
		for_each_ref(clear_marks, NULL);
	marked = 1;
}