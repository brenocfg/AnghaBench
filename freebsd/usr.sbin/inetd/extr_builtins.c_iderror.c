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

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  MSG_EOF ; 
 int /*<<< orphan*/  asprintf (char**,char*,int,int,char const*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  send (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
iderror(int lport, int fport, int s, const char *er)
{
	char *p;

	asprintf(&p, "%d , %d : ERROR : %s\r\n", lport, fport, er);
	if (p == NULL) {
		syslog(LOG_ERR, "asprintf: %m");
		exit(EX_OSERR);
	}
	send(s, p, strlen(p), MSG_EOF);
	free(p);

	exit(0);
}