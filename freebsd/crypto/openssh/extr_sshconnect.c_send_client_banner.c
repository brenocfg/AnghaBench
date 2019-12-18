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
struct TYPE_2__ {char* version_addendum; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROTOCOL_MAJOR_2 ; 
 int /*<<< orphan*/  PROTOCOL_MINOR_2 ; 
 int /*<<< orphan*/  SSH_VERSION ; 
 scalar_t__ atomicio (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  chop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  client_version_string ; 
 int /*<<< orphan*/  debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ options ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vwrite ; 
 int /*<<< orphan*/  xasprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void
send_client_banner(int connection_out, int minor1)
{
	/* Send our own protocol version identification. */
	xasprintf(&client_version_string, "SSH-%d.%d-%.100s%s%s\n",
	    PROTOCOL_MAJOR_2, PROTOCOL_MINOR_2, SSH_VERSION,
	    *options.version_addendum == '\0' ? "" : " ",
	    options.version_addendum);
	if (atomicio(vwrite, connection_out, client_version_string,
	    strlen(client_version_string)) != strlen(client_version_string))
		fatal("write: %.100s", strerror(errno));
	chop(client_version_string);
	debug("Local version string %.100s", client_version_string);
}