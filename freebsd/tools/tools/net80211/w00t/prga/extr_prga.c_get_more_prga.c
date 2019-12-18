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
#define  S_SEND_FRAG 131 
#define  S_START 130 
#define  S_WAIT_ACK 129 
#define  S_WAIT_RELAY 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  send_frag (struct params*) ; 
 int /*<<< orphan*/  start (struct params*) ; 
 int /*<<< orphan*/  wait_ack (struct params*) ; 
 int /*<<< orphan*/  wait_relay (struct params*) ; 

void get_more_prga(struct params *p)
{
	switch (p->state) {
	case S_START:
		start(p);
		break;

	case S_SEND_FRAG:
		send_frag(p);
		break;

	case S_WAIT_ACK:
		wait_ack(p);
		break;

	case S_WAIT_RELAY:
		wait_relay(p);
		break;

	default:
		printf("WTF %d\n", p->state);
		abort();
		break;
	}
}