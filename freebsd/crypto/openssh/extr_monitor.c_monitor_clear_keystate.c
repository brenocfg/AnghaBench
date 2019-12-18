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
struct ssh {int dummy; } ;
struct monitor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODE_IN ; 
 int /*<<< orphan*/  MODE_OUT ; 
 struct ssh* active_state ; 
 int /*<<< orphan*/ * child_state ; 
 int /*<<< orphan*/  ssh_clear_newkeys (struct ssh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshbuf_free (int /*<<< orphan*/ *) ; 

void
monitor_clear_keystate(struct monitor *pmonitor)
{
	struct ssh *ssh = active_state;	/* XXX */

	ssh_clear_newkeys(ssh, MODE_IN);
	ssh_clear_newkeys(ssh, MODE_OUT);
	sshbuf_free(child_state);
	child_state = NULL;
}