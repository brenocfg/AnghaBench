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
typedef  int time_t ;
struct ssh {TYPE_1__* state; } ;
struct TYPE_2__ {int rekey_time; int rekey_interval; } ;

/* Variables and functions */
 int monotime () ; 

time_t
ssh_packet_get_rekey_timeout(struct ssh *ssh)
{
	time_t seconds;

	seconds = ssh->state->rekey_time + ssh->state->rekey_interval -
	    monotime();
	return (seconds <= 0 ? 1 : seconds);
}