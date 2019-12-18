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

/* Variables and functions */
 int /*<<< orphan*/  SSH2_MSG_KEX_DH_GEX_REQUEST ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  input_kex_dh_gex_request ; 
 int /*<<< orphan*/  ssh_dispatch_set (struct ssh*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
kexgex_server(struct ssh *ssh)
{
	ssh_dispatch_set(ssh, SSH2_MSG_KEX_DH_GEX_REQUEST,
	    &input_kex_dh_gex_request);
	debug("expecting SSH2_MSG_KEX_DH_GEX_REQUEST");
	return 0;
}