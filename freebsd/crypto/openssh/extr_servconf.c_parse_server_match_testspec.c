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
struct connection_info {int lport; void* rdomain; void* laddress; void* user; void* host; void* address; } ;

/* Variables and functions */
 int a2port (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strsep (char**,char*) ; 
 void* xstrdup (char*) ; 

int parse_server_match_testspec(struct connection_info *ci, char *spec)
{
	char *p;

	while ((p = strsep(&spec, ",")) && *p != '\0') {
		if (strncmp(p, "addr=", 5) == 0) {
			ci->address = xstrdup(p + 5);
		} else if (strncmp(p, "host=", 5) == 0) {
			ci->host = xstrdup(p + 5);
		} else if (strncmp(p, "user=", 5) == 0) {
			ci->user = xstrdup(p + 5);
		} else if (strncmp(p, "laddr=", 6) == 0) {
			ci->laddress = xstrdup(p + 6);
		} else if (strncmp(p, "rdomain=", 8) == 0) {
			ci->rdomain = xstrdup(p + 8);
		} else if (strncmp(p, "lport=", 6) == 0) {
			ci->lport = a2port(p + 6);
			if (ci->lport == -1) {
				fprintf(stderr, "Invalid port '%s' in test mode"
				   " specification %s\n", p+6, p);
				return -1;
			}
		} else {
			fprintf(stderr, "Invalid test mode specification %s\n",
			   p);
			return -1;
		}
	}
	return 0;
}