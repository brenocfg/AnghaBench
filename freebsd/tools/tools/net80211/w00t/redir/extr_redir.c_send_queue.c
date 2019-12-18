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
struct queue {struct queue* live; } ;
struct params {int /*<<< orphan*/  state; struct queue* q; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_WAIT_ACK ; 
 int /*<<< orphan*/  assert (struct queue*) ; 
 int /*<<< orphan*/  send_header (struct params*,struct queue*) ; 

void send_queue(struct params *p)
{
	struct queue *q = p->q;

	assert(q);
	assert(q->live);

	send_header(p, q);
	p->state = S_WAIT_ACK;
}