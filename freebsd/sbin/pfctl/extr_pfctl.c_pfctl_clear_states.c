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
struct pfioc_state_kill {int psk_killed; int /*<<< orphan*/  psk_ifname; } ;
typedef  int /*<<< orphan*/  psk ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCCLRSTATES ; 
 int PF_OPT_QUIET ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct pfioc_state_kill*) ; 
 int /*<<< orphan*/  memset (struct pfioc_state_kill*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

int
pfctl_clear_states(int dev, const char *iface, int opts)
{
	struct pfioc_state_kill psk;

	memset(&psk, 0, sizeof(psk));
	if (iface != NULL && strlcpy(psk.psk_ifname, iface,
	    sizeof(psk.psk_ifname)) >= sizeof(psk.psk_ifname))
		errx(1, "invalid interface: %s", iface);

	if (ioctl(dev, DIOCCLRSTATES, &psk))
		err(1, "DIOCCLRSTATES");
	if ((opts & PF_OPT_QUIET) == 0)
		fprintf(stderr, "%d states cleared\n", psk.psk_killed);
	return (0);
}