#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  msg ;
struct TYPE_4__ {int msgh_id; int /*<<< orphan*/  msgh_bits; int /*<<< orphan*/  msgh_local_port; int /*<<< orphan*/  msgh_remote_port; } ;
struct TYPE_3__ {TYPE_2__ header; } ;
typedef  TYPE_1__ mach_msg_empty_send_t ;

/* Variables and functions */
 int /*<<< orphan*/  MACH_MSGH_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_MSG_TIMEOUT_NONE ; 
 int /*<<< orphan*/  MACH_MSG_TYPE_MAKE_SEND ; 
 int /*<<< orphan*/  MACH_PORT_NULL ; 
 int MACH_SEND_MSG ; 
 int MACH_SEND_TIMEOUT ; 
 int /*<<< orphan*/  mach_msg (TYPE_2__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_port ; 

void
auditd_relay_signal(int signal)
{
	mach_msg_empty_send_t msg;

	msg.header.msgh_id = signal;
	msg.header.msgh_remote_port = signal_port;
	msg.header.msgh_local_port = MACH_PORT_NULL;
	msg.header.msgh_bits = MACH_MSGH_BITS(MACH_MSG_TYPE_MAKE_SEND, 0);
	mach_msg(&(msg.header), MACH_SEND_MSG|MACH_SEND_TIMEOUT, sizeof(msg),
	    0, MACH_PORT_NULL, MACH_MSG_TIMEOUT_NONE, MACH_PORT_NULL);
}