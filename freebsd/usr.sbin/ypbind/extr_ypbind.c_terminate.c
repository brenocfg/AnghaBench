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
struct _dom_binding {char* dom_domain; int /*<<< orphan*/  dom_vers; scalar_t__ dom_broadcast_pid; int /*<<< orphan*/  dom_lockfd; struct _dom_binding* dom_pnext; } ;

/* Variables and functions */
 char* BINDINGDIR ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  SIGINT ; 
 char* YPBINDLOCK ; 
 int /*<<< orphan*/  YPBINDPROG ; 
 int /*<<< orphan*/  YPBINDVERS ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_unset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ppid ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 struct _dom_binding* ypbindlist ; 
 int /*<<< orphan*/  yplockfd ; 

void
terminate(int sig)
{
	struct _dom_binding *ypdb;
	char path[MAXPATHLEN];

	if (ppid != getpid())
		exit(0);

	for (ypdb = ypbindlist; ypdb; ypdb = ypdb->dom_pnext) {
		close(ypdb->dom_lockfd);
		if (ypdb->dom_broadcast_pid)
			kill(ypdb->dom_broadcast_pid, SIGINT);
		sprintf(path, "%s/%s.%ld", BINDINGDIR,
			ypdb->dom_domain, ypdb->dom_vers);
		unlink(path);
	}
	close(yplockfd);
	unlink(YPBINDLOCK);
	pmap_unset(YPBINDPROG, YPBINDVERS);
	exit(0);
}