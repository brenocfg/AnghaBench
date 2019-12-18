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
struct command {char* action; char const* name; } ;

/* Variables and functions */
 int SIZE ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 
 int strtol (char*,char**,int) ; 
 int system (char*) ; 
 int verbose ; 

void
docmd(struct command *cmd, int value, const char *hid, int argc, char **argv)
{
	char cmdbuf[SIZE], *p, *q;
	size_t len;
	int n, r;

	for (p = cmd->action, q = cmdbuf; *p && q < &cmdbuf[SIZE-1]; ) {
		if (*p == '$') {
			p++;
			len = &cmdbuf[SIZE-1] - q;
			if (isdigit(*p)) {
				n = strtol(p, &p, 10) - 1;
				if (n >= 0 && n < argc) {
					strncpy(q, argv[n], len);
					q += strlen(q);
				}
			} else if (*p == 'V') {
				p++;
				snprintf(q, len, "%d", value);
				q += strlen(q);
			} else if (*p == 'N') {
				p++;
				strncpy(q, cmd->name, len);
				q += strlen(q);
			} else if (*p == 'H') {
				p++;
				strncpy(q, hid, len);
				q += strlen(q);
			} else if (*p) {
				*q++ = *p++;
			}
		} else {
			*q++ = *p++;
		}
	}
	*q = 0;

	if (verbose)
		printf("system '%s'\n", cmdbuf);
	r = system(cmdbuf);
	if (verbose > 1 && r)
		printf("return code = 0x%x\n", r);
}