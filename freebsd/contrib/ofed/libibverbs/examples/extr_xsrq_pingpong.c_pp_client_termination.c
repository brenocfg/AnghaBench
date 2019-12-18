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

/* Variables and functions */
 scalar_t__ recv_termination_ack (int /*<<< orphan*/ ) ; 
 scalar_t__ send_termination_ack (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pp_client_termination(void)
{
	if (send_termination_ack(0))
		return 1;
	if (recv_termination_ack(0))
		return 1;

	return 0;
}