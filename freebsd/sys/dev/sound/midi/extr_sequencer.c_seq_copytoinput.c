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
typedef  int /*<<< orphan*/  u_char ;
struct seq_softc {int /*<<< orphan*/  in_cv; int /*<<< orphan*/  in_sel; int /*<<< orphan*/  in_q; int /*<<< orphan*/  seq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int MIDIQ_AVAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIDIQ_ENQ (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SEQ_DEBUG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  selwakeup (int /*<<< orphan*/ *) ; 

void
seq_copytoinput(struct seq_softc *scp, u_char *event, int len)
{

	mtx_assert(&scp->seq_lock, MA_OWNED);

	if (MIDIQ_AVAIL(scp->in_q) < len) {
		/*
	         * ENOROOM?  EINPUTDROPPED? ETOUGHLUCK?
	         */
		SEQ_DEBUG(2, printf("seq_copytoinput: queue full\n"));
	} else {
		MIDIQ_ENQ(scp->in_q, event, len);
		selwakeup(&scp->in_sel);
		cv_broadcast(&scp->in_cv);
	}

}