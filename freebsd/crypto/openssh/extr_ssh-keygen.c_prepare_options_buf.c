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
struct sshbuf {int dummy; } ;
struct TYPE_2__ {char* key; int /*<<< orphan*/ * val; scalar_t__ crit; } ;

/* Variables and functions */
 int CERTOPT_AGENT_FWD ; 
 int CERTOPT_PORT_FWD ; 
 int CERTOPT_PTY ; 
 int CERTOPT_USER_RC ; 
 int CERTOPT_X_FWD ; 
 int OPTIONS_CRITICAL ; 
 int OPTIONS_EXTENSIONS ; 
 int /*<<< orphan*/  add_flag_option (struct sshbuf*,char*) ; 
 int /*<<< orphan*/  add_string_option (struct sshbuf*,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__* cert_userext ; 
 int /*<<< orphan*/ * certflags_command ; 
 int certflags_flags ; 
 int /*<<< orphan*/ * certflags_src_addr ; 
 size_t ncert_userext ; 
 int /*<<< orphan*/  sshbuf_reset (struct sshbuf*) ; 

__attribute__((used)) static void
prepare_options_buf(struct sshbuf *c, int which)
{
	size_t i;

	sshbuf_reset(c);
	if ((which & OPTIONS_CRITICAL) != 0 &&
	    certflags_command != NULL)
		add_string_option(c, "force-command", certflags_command);
	if ((which & OPTIONS_EXTENSIONS) != 0 &&
	    (certflags_flags & CERTOPT_X_FWD) != 0)
		add_flag_option(c, "permit-X11-forwarding");
	if ((which & OPTIONS_EXTENSIONS) != 0 &&
	    (certflags_flags & CERTOPT_AGENT_FWD) != 0)
		add_flag_option(c, "permit-agent-forwarding");
	if ((which & OPTIONS_EXTENSIONS) != 0 &&
	    (certflags_flags & CERTOPT_PORT_FWD) != 0)
		add_flag_option(c, "permit-port-forwarding");
	if ((which & OPTIONS_EXTENSIONS) != 0 &&
	    (certflags_flags & CERTOPT_PTY) != 0)
		add_flag_option(c, "permit-pty");
	if ((which & OPTIONS_EXTENSIONS) != 0 &&
	    (certflags_flags & CERTOPT_USER_RC) != 0)
		add_flag_option(c, "permit-user-rc");
	if ((which & OPTIONS_CRITICAL) != 0 &&
	    certflags_src_addr != NULL)
		add_string_option(c, "source-address", certflags_src_addr);
	for (i = 0; i < ncert_userext; i++) {
		if ((cert_userext[i].crit && (which & OPTIONS_EXTENSIONS)) ||
		    (!cert_userext[i].crit && (which & OPTIONS_CRITICAL)))
			continue;
		if (cert_userext[i].val == NULL)
			add_flag_option(c, cert_userext[i].key);
		else {
			add_string_option(c, cert_userext[i].key,
			    cert_userext[i].val);
		}
	}
}