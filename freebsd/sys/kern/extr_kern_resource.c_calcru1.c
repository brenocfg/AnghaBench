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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint64_t ;
struct timeval {int tv_sec; int tv_usec; } ;
struct rusage_ext {int rux_uticks; int rux_sticks; int rux_iticks; int rux_tu; int rux_uu; int rux_su; int /*<<< orphan*/  rux_runtime; } ;
struct proc {int /*<<< orphan*/  p_comm; int /*<<< orphan*/  p_pid; } ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ __predict_true (int) ; 
 int cputick2usec (int /*<<< orphan*/ ) ; 
 int mul64_by_fraction (int,int,int) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
calcru1(struct proc *p, struct rusage_ext *ruxp, struct timeval *up,
    struct timeval *sp)
{
	/* {user, system, interrupt, total} {ticks, usec}: */
	uint64_t ut, uu, st, su, it, tt, tu;

	ut = ruxp->rux_uticks;
	st = ruxp->rux_sticks;
	it = ruxp->rux_iticks;
	tt = ut + st + it;
	if (tt == 0) {
		/* Avoid divide by zero */
		st = 1;
		tt = 1;
	}
	tu = cputick2usec(ruxp->rux_runtime);
	if ((int64_t)tu < 0) {
		/* XXX: this should be an assert /phk */
		printf("calcru: negative runtime of %jd usec for pid %d (%s)\n",
		    (intmax_t)tu, p->p_pid, p->p_comm);
		tu = ruxp->rux_tu;
	}

	/* Subdivide tu.  Avoid overflow in the multiplications. */
	if (__predict_true(tu <= ((uint64_t)1 << 38) && tt <= (1 << 26))) {
		/* Up to 76 hours when stathz is 128. */
		uu = (tu * ut) / tt;
		su = (tu * st) / tt;
	} else {
		uu = mul64_by_fraction(tu, ut, tt);
		su = mul64_by_fraction(tu, st, tt);
	}

	if (tu >= ruxp->rux_tu) {
		/*
		 * The normal case, time increased.
		 * Enforce monotonicity of bucketed numbers.
		 */
		if (uu < ruxp->rux_uu)
			uu = ruxp->rux_uu;
		if (su < ruxp->rux_su)
			su = ruxp->rux_su;
	} else if (tu + 3 > ruxp->rux_tu || 101 * tu > 100 * ruxp->rux_tu) {
		/*
		 * When we calibrate the cputicker, it is not uncommon to
		 * see the presumably fixed frequency increase slightly over
		 * time as a result of thermal stabilization and NTP
		 * discipline (of the reference clock).  We therefore ignore
		 * a bit of backwards slop because we  expect to catch up
		 * shortly.  We use a 3 microsecond limit to catch low
		 * counts and a 1% limit for high counts.
		 */
		uu = ruxp->rux_uu;
		su = ruxp->rux_su;
		tu = ruxp->rux_tu;
	} else { /* tu < ruxp->rux_tu */
		/*
		 * What happened here was likely that a laptop, which ran at
		 * a reduced clock frequency at boot, kicked into high gear.
		 * The wisdom of spamming this message in that case is
		 * dubious, but it might also be indicative of something
		 * serious, so lets keep it and hope laptops can be made
		 * more truthful about their CPU speed via ACPI.
		 */
		printf("calcru: runtime went backwards from %ju usec "
		    "to %ju usec for pid %d (%s)\n",
		    (uintmax_t)ruxp->rux_tu, (uintmax_t)tu,
		    p->p_pid, p->p_comm);
	}

	ruxp->rux_uu = uu;
	ruxp->rux_su = su;
	ruxp->rux_tu = tu;

	up->tv_sec = uu / 1000000;
	up->tv_usec = uu % 1000000;
	sp->tv_sec = su / 1000000;
	sp->tv_usec = su % 1000000;
}