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
struct pfioc_iface {int pfiio_esize; int pfiio_size; struct pfi_kif* pfiio_buffer; } ;
struct pfi_kif {int index; int /*<<< orphan*/  pfi; } ;
struct pfi_entry {int index; int /*<<< orphan*/  pfi; } ;
typedef  int /*<<< orphan*/  io ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCIGETIFACES ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct pfi_kif* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pfi_kif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct pfi_kif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct pfioc_iface*,int) ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct pfi_kif*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pfioc_iface*) ; 
 int /*<<< orphan*/  link ; 
 struct pfi_kif* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct pfi_kif*,int) ; 
 scalar_t__ pf_tick ; 
 int /*<<< orphan*/  pfi_table ; 
 int /*<<< orphan*/  pfi_table_age ; 
 int pfi_table_count ; 
 struct pfi_kif* reallocf (struct pfi_kif*,int) ; 
 scalar_t__ started ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ this_tick ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pfi_refresh(void)
{
	struct pfioc_iface io;
	struct pfi_kif *p = NULL;
	struct pfi_entry *e;
	int i, numifs = 1;

	if (started && this_tick <= pf_tick)
		return (0);

	while (!TAILQ_EMPTY(&pfi_table)) {
		e = TAILQ_FIRST(&pfi_table);
		TAILQ_REMOVE(&pfi_table, e, link);
		free(e);
	}

	bzero(&io, sizeof(io));
	io.pfiio_esize = sizeof(struct pfi_kif);

	for (;;) {
		p = reallocf(p, numifs * sizeof(struct pfi_kif));
		if (p == NULL) {
			syslog(LOG_ERR, "pfi_refresh(): reallocf() numifs=%d: %s",
			    numifs, strerror(errno));
			goto err2;
		}
		io.pfiio_size = numifs;
		io.pfiio_buffer = p;

		if (ioctl(dev, DIOCIGETIFACES, &io)) {
			syslog(LOG_ERR, "pfi_refresh(): ioctl(): %s",
			    strerror(errno));
			goto err2;
		}

		if (numifs >= io.pfiio_size)
			break;

		numifs = io.pfiio_size;
	}

	for (i = 0; i < numifs; i++) {
		e = malloc(sizeof(struct pfi_entry));
		if (e == NULL)
			goto err1;
		e->index = i + 1;
		memcpy(&e->pfi, p+i, sizeof(struct pfi_kif));
		TAILQ_INSERT_TAIL(&pfi_table, e, link);
	}

	pfi_table_age = time(NULL);
	pfi_table_count = numifs;
	pf_tick = this_tick;

	free(p);
	return (0);

err1:
	while (!TAILQ_EMPTY(&pfi_table)) {
		e = TAILQ_FIRST(&pfi_table);
		TAILQ_REMOVE(&pfi_table, e, link);
		free(e);
	}
err2:
	free(p);
	return(-1);
}