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
struct TYPE_2__ {int num_clients; } ;

/* Variables and functions */
 TYPE_1__ ctx ; 
 scalar_t__ recv_termination_ack (int) ; 
 scalar_t__ send_termination_ack (int) ; 

__attribute__((used)) static int pp_server_termination(void)
{
	int i;

	for (i = 0; i < ctx.num_clients; i++) {
		if (recv_termination_ack(i))
			return 1;
	}

	for (i = 0; i < ctx.num_clients; i++) {
		if (send_termination_ack(i))
			return 1;
	}

	return 0;
}