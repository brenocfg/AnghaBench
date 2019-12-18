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
typedef  scalar_t__ u_int64_t ;
typedef  scalar_t__ u_int32_t ;
struct ssh {TYPE_1__* state; } ;
struct TYPE_2__ {scalar_t__ rekey_interval; scalar_t__ rekey_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug3 (char*,unsigned long long,unsigned int) ; 

void
ssh_packet_set_rekey_limits(struct ssh *ssh, u_int64_t bytes, u_int32_t seconds)
{
	debug3("rekey after %llu bytes, %u seconds", (unsigned long long)bytes,
	    (unsigned int)seconds);
	ssh->state->rekey_limit = bytes;
	ssh->state->rekey_interval = seconds;
}