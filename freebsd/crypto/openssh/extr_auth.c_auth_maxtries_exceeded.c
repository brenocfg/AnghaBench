#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ssh {int dummy; } ;
struct TYPE_3__ {char* user; scalar_t__ valid; } ;
typedef  TYPE_1__ Authctxt ;

/* Variables and functions */
 struct ssh* active_state ; 
 int /*<<< orphan*/  error (char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packet_disconnect (char*) ; 
 int /*<<< orphan*/  ssh_remote_ipaddr (struct ssh*) ; 
 int /*<<< orphan*/  ssh_remote_port (struct ssh*) ; 

void
auth_maxtries_exceeded(Authctxt *authctxt)
{
	struct ssh *ssh = active_state; /* XXX */

	error("maximum authentication attempts exceeded for "
	    "%s%.100s from %.200s port %d ssh2",
	    authctxt->valid ? "" : "invalid user ",
	    authctxt->user,
	    ssh_remote_ipaddr(ssh),
	    ssh_remote_port(ssh));
	packet_disconnect("Too many authentication failures");
	/* NOTREACHED */
}