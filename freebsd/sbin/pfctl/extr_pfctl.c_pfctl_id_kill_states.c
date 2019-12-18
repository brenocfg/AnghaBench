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
struct TYPE_2__ {scalar_t__ id; scalar_t__ creatorid; } ;
struct pfioc_state_kill {int psk_killed; TYPE_1__ psk_pfcmp; } ;
typedef  int /*<<< orphan*/  psk ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCKILLSTATES ; 
 int /*<<< orphan*/  HTONL (scalar_t__) ; 
 int PF_OPT_QUIET ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ htobe64 (scalar_t__) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct pfioc_state_kill*) ; 
 int /*<<< orphan*/  memset (struct pfioc_state_kill*,int /*<<< orphan*/ ,int) ; 
 int sscanf (int /*<<< orphan*/ ,char*,scalar_t__*,...) ; 
 int /*<<< orphan*/ * state_kill ; 
 int state_killers ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
pfctl_id_kill_states(int dev, const char *iface, int opts)
{
	struct pfioc_state_kill psk;
	
	if (state_killers != 2 || (strlen(state_kill[1]) == 0)) {
		warnx("no id specified");
		usage();
	}

	memset(&psk, 0, sizeof(psk));
	if ((sscanf(state_kill[1], "%jx/%x",
	    &psk.psk_pfcmp.id, &psk.psk_pfcmp.creatorid)) == 2)
		HTONL(psk.psk_pfcmp.creatorid);
	else if ((sscanf(state_kill[1], "%jx", &psk.psk_pfcmp.id)) == 1) {
		psk.psk_pfcmp.creatorid = 0;
	} else {
		warnx("wrong id format specified");
		usage();
	}
	if (psk.psk_pfcmp.id == 0) {
		warnx("cannot kill id 0");
		usage();
	}

	psk.psk_pfcmp.id = htobe64(psk.psk_pfcmp.id);
	if (ioctl(dev, DIOCKILLSTATES, &psk))
		err(1, "DIOCKILLSTATES");

	if ((opts & PF_OPT_QUIET) == 0)
		fprintf(stderr, "killed %d states\n", psk.psk_killed);

	return (0);
}