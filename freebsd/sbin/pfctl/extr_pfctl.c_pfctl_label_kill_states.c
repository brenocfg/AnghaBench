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
struct pfioc_state_kill {int psk_killed; int /*<<< orphan*/  psk_label; int /*<<< orphan*/  psk_ifname; } ;
typedef  int /*<<< orphan*/  psk ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCKILLSTATES ; 
 int PF_OPT_QUIET ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct pfioc_state_kill*) ; 
 int /*<<< orphan*/  memset (struct pfioc_state_kill*,int /*<<< orphan*/ ,int) ; 
 char const** state_kill ; 
 int state_killers ; 
 int /*<<< orphan*/  stderr ; 
 int strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
pfctl_label_kill_states(int dev, const char *iface, int opts)
{
	struct pfioc_state_kill psk;

	if (state_killers != 2 || (strlen(state_kill[1]) == 0)) {
		warnx("no label specified");
		usage();
	}
	memset(&psk, 0, sizeof(psk));
	if (iface != NULL && strlcpy(psk.psk_ifname, iface,
	    sizeof(psk.psk_ifname)) >= sizeof(psk.psk_ifname))
		errx(1, "invalid interface: %s", iface);

	if (strlcpy(psk.psk_label, state_kill[1], sizeof(psk.psk_label)) >=
	    sizeof(psk.psk_label))
		errx(1, "label too long: %s", state_kill[1]);

	if (ioctl(dev, DIOCKILLSTATES, &psk))
		err(1, "DIOCKILLSTATES");

	if ((opts & PF_OPT_QUIET) == 0)
		fprintf(stderr, "killed %d states\n", psk.psk_killed);

	return (0);
}