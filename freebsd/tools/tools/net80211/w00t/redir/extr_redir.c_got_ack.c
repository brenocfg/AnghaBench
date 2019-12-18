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
struct params {int frag; int data_try; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_WAIT_BUDDY ; 
 int /*<<< orphan*/  send_data (struct params*) ; 

void got_ack(struct params *p)
{
	switch (p->frag) {
	case 1:
		send_data(p);
		break;

	case 2:
		p->state = S_WAIT_BUDDY;
		p->data_try = 69;
		break;
	}
}