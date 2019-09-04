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
struct fetch_negotiator {struct data* data; int /*<<< orphan*/  release; int /*<<< orphan*/  ack; int /*<<< orphan*/  next; int /*<<< orphan*/  add_tip; int /*<<< orphan*/  known_common; } ;
struct TYPE_2__ {int /*<<< orphan*/  compare; } ;
struct data {TYPE_1__ rev_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ack ; 
 int /*<<< orphan*/  add_tip ; 
 int /*<<< orphan*/  clear_marks ; 
 int /*<<< orphan*/  compare ; 
 int /*<<< orphan*/  for_each_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  known_common ; 
 int marked ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  release ; 
 struct data* xcalloc (int,int) ; 

void skipping_negotiator_init(struct fetch_negotiator *negotiator)
{
	struct data *data;
	negotiator->known_common = known_common;
	negotiator->add_tip = add_tip;
	negotiator->next = next;
	negotiator->ack = ack;
	negotiator->release = release;
	negotiator->data = data = xcalloc(1, sizeof(*data));
	data->rev_list.compare = compare;

	if (marked)
		for_each_ref(clear_marks, NULL);
	marked = 1;
}