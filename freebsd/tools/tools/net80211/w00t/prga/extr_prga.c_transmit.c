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
struct params {int state; } ;

/* Variables and functions */
#define  S_START 129 
#define  S_WAIT_ACK 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  read_tap (struct params*) ; 
 int /*<<< orphan*/  wait_tap_ack (struct params*) ; 

void transmit(struct params *p)
{
	switch (p->state) {
	case S_START:
		read_tap(p);
		break;
	
	case S_WAIT_ACK:
		wait_tap_ack(p);
		break;

	default:
		printf("wtf %d\n", p->state);
		abort();
		break;
	}
}