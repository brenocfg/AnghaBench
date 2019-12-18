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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  u_int ;
struct ssh {TYPE_1__* authctxt; } ;
struct TYPE_2__ {int /*<<< orphan*/  success; } ;
typedef  TYPE_1__ Authctxt ;

/* Variables and functions */
 int /*<<< orphan*/  SSH2_MSG_SERVICE_ACCEPT ; 
 int /*<<< orphan*/  SSH2_MSG_USERAUTH_REQUEST ; 
 int /*<<< orphan*/  debug (char*,char*) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  input_userauth_request ; 
 int /*<<< orphan*/  packet_check_eom () ; 
 int /*<<< orphan*/  packet_disconnect (char*,char*) ; 
 char* packet_get_cstring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_put_cstring (char*) ; 
 int /*<<< orphan*/  packet_send () ; 
 int /*<<< orphan*/  packet_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packet_write_wait () ; 
 int /*<<< orphan*/  ssh_dispatch_set (struct ssh*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
input_service_request(int type, u_int32_t seq, struct ssh *ssh)
{
	Authctxt *authctxt = ssh->authctxt;
	u_int len;
	int acceptit = 0;
	char *service = packet_get_cstring(&len);
	packet_check_eom();

	if (authctxt == NULL)
		fatal("input_service_request: no authctxt");

	if (strcmp(service, "ssh-userauth") == 0) {
		if (!authctxt->success) {
			acceptit = 1;
			/* now we can handle user-auth requests */
			ssh_dispatch_set(ssh, SSH2_MSG_USERAUTH_REQUEST, &input_userauth_request);
		}
	}
	/* XXX all other service requests are denied */

	if (acceptit) {
		packet_start(SSH2_MSG_SERVICE_ACCEPT);
		packet_put_cstring(service);
		packet_send();
		packet_write_wait();
	} else {
		debug("bad service request %s", service);
		packet_disconnect("bad service request %s", service);
	}
	free(service);
	return 0;
}