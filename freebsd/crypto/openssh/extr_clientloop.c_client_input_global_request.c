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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ssh {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSH2_MSG_REQUEST_FAILURE ; 
 int /*<<< orphan*/  SSH2_MSG_REQUEST_SUCCESS ; 
 int client_input_hostkeys () ; 
 int /*<<< orphan*/  debug (char*,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int packet_get_char () ; 
 char* packet_get_cstring (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_send () ; 
 int /*<<< orphan*/  packet_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packet_write_wait () ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
client_input_global_request(int type, u_int32_t seq, struct ssh *ssh)
{
	char *rtype;
	int want_reply;
	int success = 0;

	rtype = packet_get_cstring(NULL);
	want_reply = packet_get_char();
	debug("client_input_global_request: rtype %s want_reply %d",
	    rtype, want_reply);
	if (strcmp(rtype, "hostkeys-00@openssh.com") == 0)
		success = client_input_hostkeys();
	if (want_reply) {
		packet_start(success ?
		    SSH2_MSG_REQUEST_SUCCESS : SSH2_MSG_REQUEST_FAILURE);
		packet_send();
		packet_write_wait();
	}
	free(rtype);
	return 0;
}