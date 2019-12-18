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
typedef  int uint64_t ;
struct targ {int fd; int used; int me; int affinity; int /*<<< orphan*/  thread; int /*<<< orphan*/  frags; struct nm_desc* nmd; struct glob_arg* g; int /*<<< orphan*/  seed; } ;
struct TYPE_2__ {int nr_flags; int nr_ringid; } ;
struct nm_desc {int fd; TYPE_1__ req; struct nm_desc* self; } ;
struct glob_arg {int nthreads; scalar_t__ dev_type; scalar_t__ td_type; int ifname; int main_fd; int affinity; int cpus; int /*<<< orphan*/  td_body; int /*<<< orphan*/  wait_link; int /*<<< orphan*/  frags; struct nm_desc* nmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*,...) ; 
 scalar_t__ DEV_NETMAP ; 
 int NETMAP_NO_TX_POLL ; 
 int NM_OPEN_IFNAME ; 
 int NM_OPEN_NO_MMAP ; 
 int NR_REG_MASK ; 
 int NR_REG_ONE_NIC ; 
 scalar_t__ TD_TYPE_RECEIVER ; 
 int /*<<< orphan*/  bzero (struct targ*,int) ; 
 struct targ* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  initialize_packet (struct targ*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 struct nm_desc* nm_open (int,int /*<<< orphan*/ *,int,struct nm_desc*) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct targ*) ; 
 int /*<<< orphan*/  sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 struct targ* targs ; 
 int time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
start_threads(struct glob_arg *g) {
	int i;

	targs = calloc(g->nthreads, sizeof(*targs));
	struct targ *t;
	/*
	 * Now create the desired number of threads, each one
	 * using a single descriptor.
	 */
	for (i = 0; i < g->nthreads; i++) {
		uint64_t seed = time(0) | (time(0) << 32);
		t = &targs[i];

		bzero(t, sizeof(*t));
		t->fd = -1; /* default, with pcap */
		t->g = g;
		memcpy(t->seed, &seed, sizeof(t->seed));

		if (g->dev_type == DEV_NETMAP) {
			struct nm_desc nmd = *g->nmd; /* copy, we overwrite ringid */
			uint64_t nmd_flags = 0;
			nmd.self = &nmd;

			if (i > 0) {
				/* the first thread uses the fd opened by the main
				 * thread, the other threads re-open /dev/netmap
				 */
				if (g->nthreads > 1) {
					nmd.req.nr_flags =
						g->nmd->req.nr_flags & ~NR_REG_MASK;
					nmd.req.nr_flags |= NR_REG_ONE_NIC;
					nmd.req.nr_ringid = i;
				}
				/* Only touch one of the rings (rx is already ok) */
				if (g->td_type == TD_TYPE_RECEIVER)
					nmd_flags |= NETMAP_NO_TX_POLL;

				/* register interface. Override ifname and ringid etc. */
				t->nmd = nm_open(t->g->ifname, NULL, nmd_flags |
						NM_OPEN_IFNAME | NM_OPEN_NO_MMAP, &nmd);
				if (t->nmd == NULL) {
					D("Unable to open %s: %s",
							t->g->ifname, strerror(errno));
					continue;
				}
			} else {
				t->nmd = g->nmd;
			}
			t->fd = t->nmd->fd;
			t->frags = g->frags;
		} else {
			targs[i].fd = g->main_fd;
		}
		t->used = 1;
		t->me = i;
		if (g->affinity >= 0) {
			t->affinity = (g->affinity + i) % g->cpus;
		} else {
			t->affinity = -1;
		}
		/* default, init packets */
		initialize_packet(t);
	}
	/* Wait for PHY reset. */
	D("Wait %d secs for phy reset", g->wait_link);
	sleep(g->wait_link);
	D("Ready...");

	for (i = 0; i < g->nthreads; i++) {
		t = &targs[i];
		if (pthread_create(&t->thread, NULL, g->td_body, t) == -1) {
			D("Unable to create thread %d: %s", i, strerror(errno));
			t->used = 0;
		}
	}
}