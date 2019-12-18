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
 int SSH_ERR_ALLOC_FAIL ; 
 char* SSH_VERSION ; 
 int /*<<< orphan*/  chop (char*) ; 
 int /*<<< orphan*/  debug (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  ssh_packet_get_output (struct ssh*) ; 
 int sshbuf_put (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int
_ssh_send_banner(struct ssh *ssh, char **bannerp)
{
	char buf[256];
	int r;

	snprintf(buf, sizeof buf, "SSH-2.0-%.100s\r\n", SSH_VERSION);
	if ((r = sshbuf_put(ssh_packet_get_output(ssh), buf, strlen(buf))) != 0)
		return r;
	chop(buf);
	debug("Local version string %.100s", buf);
	if ((*bannerp = strdup(buf)) == NULL)
		return SSH_ERR_ALLOC_FAIL;
	return 0;
}