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
struct pft_entry {int index; int /*<<< orphan*/  pft; } ;
struct pfr_tstats {int index; int /*<<< orphan*/  pft; } ;
struct pfioc_table {int pfrio_esize; int pfrio_size; struct pft_entry* pfrio_buffer; } ;
typedef  int /*<<< orphan*/  io ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCRGETTSTATS ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct pft_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pft_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pft_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct pfioc_table*,int) ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct pft_entry*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pfioc_table*) ; 
 int /*<<< orphan*/  link ; 
 struct pft_entry* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct pft_entry*,int) ; 
 scalar_t__ pf_tick ; 
 int /*<<< orphan*/  pft_table ; 
 int /*<<< orphan*/  pft_table_age ; 
 int pft_table_count ; 
 struct pft_entry* reallocf (struct pft_entry*,int) ; 
 scalar_t__ started ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ this_tick ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pft_refresh(void)
{
	struct pfioc_table io;
	struct pfr_tstats *t = NULL;
	struct pft_entry *e;
	int i, numtbls = 1;

	if (started && this_tick <= pf_tick)
		return (0);

	while (!TAILQ_EMPTY(&pft_table)) {
		e = TAILQ_FIRST(&pft_table);
		TAILQ_REMOVE(&pft_table, e, link);
		free(e);
	}

	bzero(&io, sizeof(io));
	io.pfrio_esize = sizeof(struct pfr_tstats);

	for (;;) {
		t = reallocf(t, numtbls * sizeof(struct pfr_tstats));
		if (t == NULL) {
			syslog(LOG_ERR, "pft_refresh(): reallocf() numtbls=%d: %s",
			    numtbls, strerror(errno));
			goto err2;
		}
		io.pfrio_size = numtbls;
		io.pfrio_buffer = t;

		if (ioctl(dev, DIOCRGETTSTATS, &io)) {
			syslog(LOG_ERR, "pft_refresh(): ioctl(): %s",
			    strerror(errno));
			goto err2;
		}

		if (numtbls >= io.pfrio_size)
			break;

		numtbls = io.pfrio_size;
	}

	for (i = 0; i < numtbls; i++) {
		e = malloc(sizeof(struct pft_entry));
		if (e == NULL)
			goto err1;
		e->index = i + 1;
		memcpy(&e->pft, t+i, sizeof(struct pfr_tstats));
		TAILQ_INSERT_TAIL(&pft_table, e, link);
	}

	pft_table_age = time(NULL);
	pft_table_count = numtbls;
	pf_tick = this_tick;

	free(t);
	return (0);
err1:
	while (!TAILQ_EMPTY(&pft_table)) {
		e = TAILQ_FIRST(&pft_table);
		TAILQ_REMOVE(&pft_table, e, link);
		free(e);
	}
err2:
	free(t);
	return(-1);
}