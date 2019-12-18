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
struct hostinfo {int saw_extended_args; scalar_t__ hostname_lookup_done; int /*<<< orphan*/  hostname; int /*<<< orphan*/  tcp_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  canonicalize_client (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  loginfo (char*,char*) ; 
 int /*<<< orphan*/  parse_host_and_port (char*,char**,char**) ; 
 int /*<<< orphan*/  sanitize_client (int /*<<< orphan*/ *,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 

__attribute__((used)) static char *parse_host_arg(struct hostinfo *hi, char *extra_args, int buflen)
{
	char *val;
	int vallen;
	char *end = extra_args + buflen;

	if (extra_args < end && *extra_args) {
		hi->saw_extended_args = 1;
		if (strncasecmp("host=", extra_args, 5) == 0) {
			val = extra_args + 5;
			vallen = strlen(val) + 1;
			loginfo("Extended attribute \"host\": %s", val);
			if (*val) {
				/* Split <host>:<port> at colon. */
				char *host;
				char *port;
				parse_host_and_port(val, &host, &port);
				if (port)
					sanitize_client(&hi->tcp_port, port);
				canonicalize_client(&hi->hostname, host);
				hi->hostname_lookup_done = 0;
			}

			/* On to the next one */
			extra_args = val + vallen;
		}
		if (extra_args < end && *extra_args)
			die("Invalid request");
	}

	return extra_args;
}