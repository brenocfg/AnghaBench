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
struct pfr_table {int pfrio_esize; int pfrio_size; int pfrt_flags; struct pfr_table* pfrio_buffer; } ;
struct pfioc_table {int pfrio_esize; int pfrio_size; int pfrt_flags; struct pfioc_table* pfrio_buffer; } ;
struct pfa_entry {int pfrio_esize; int pfrio_size; int pfrt_flags; struct pfa_entry* pfrio_buffer; } ;
typedef  int /*<<< orphan*/  io ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCRGETTABLES ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int PFR_TFLAG_ACTIVE ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct pfr_table* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pfr_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct pfr_table*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pfr_table*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  memset (struct pfr_table*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pf_tick ; 
 int /*<<< orphan*/  pfa_table ; 
 int pfa_table_addrs (int,struct pfr_table*) ; 
 int /*<<< orphan*/  pfa_table_age ; 
 int pfa_table_count ; 
 struct pfr_table* reallocf (struct pfr_table*,int) ; 
 scalar_t__ started ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ this_tick ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pfa_refresh(void)
{
	struct pfioc_table io;
	struct pfr_table *pt = NULL, *it = NULL;
	struct pfa_entry *e;
	int i, numtbls = 1, cidx, naddrs;

	if (started && this_tick <= pf_tick)
		return (0);

	while (!TAILQ_EMPTY(&pfa_table)) {
		e = TAILQ_FIRST(&pfa_table);
		TAILQ_REMOVE(&pfa_table, e, link);
		free(e);
	}

	memset(&io, 0, sizeof(io));
	io.pfrio_esize = sizeof(struct pfr_table);

	for (;;) {
		pt = reallocf(pt, numtbls * sizeof(struct pfr_table));
		if (pt == NULL) {
			syslog(LOG_ERR, "pfa_refresh(): reallocf() %s",
			    strerror(errno));
			return (-1);
		}
		memset(pt, 0, sizeof(*pt));
		io.pfrio_size = numtbls;
		io.pfrio_buffer = pt;

		if (ioctl(dev, DIOCRGETTABLES, &io)) {
			syslog(LOG_ERR, "pfa_refresh(): ioctl(): %s",
			    strerror(errno));
			goto err2;
		}

		if (numtbls >= io.pfrio_size)
			break;

		numtbls = io.pfrio_size;
	}

	cidx = 1;

	for (it = pt, i = 0; i < numtbls; it++, i++) {
		/*
		 * Skip the table if not active - ioctl(DIOCRGETASTATS) will
		 * return ESRCH for this entry anyway.
		 */
		if (!(it->pfrt_flags & PFR_TFLAG_ACTIVE))
			continue;

		if ((naddrs = pfa_table_addrs(cidx, it)) < 0)
			goto err1;

		cidx += naddrs;
	}

	pfa_table_age = time(NULL);
	pfa_table_count = cidx;
	pf_tick = this_tick;

	free(pt);
	return (0);
err1:
	while (!TAILQ_EMPTY(&pfa_table)) {
		e = TAILQ_FIRST(&pfa_table);
		TAILQ_REMOVE(&pfa_table, e, link);
		free(e);
	}

err2:
	free(pt);
	return (-1);
}