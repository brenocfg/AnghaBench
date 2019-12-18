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
struct ub_event_base {int dummy; } ;
struct internal_base {struct ub_event_base* base; } ;
struct comm_base {struct internal_base* eb; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (struct comm_base*) ; 
 int /*<<< orphan*/  ub_comm_base_now (struct comm_base*) ; 

struct comm_base*
comm_base_create_event(struct ub_event_base* base)
{
	struct comm_base* b = (struct comm_base*)calloc(1,
		sizeof(struct comm_base));
	if(!b)
		return NULL;
	b->eb = (struct internal_base*)calloc(1, sizeof(struct internal_base));
	if(!b->eb) {
		free(b);
		return NULL;
	}
	b->eb->base = base;
	ub_comm_base_now(b);
	return b;
}