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
typedef  int u_char ;
struct seq_softc {int unit; int /*<<< orphan*/  seq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SEQ_DEBUG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static int
seq_local(struct seq_softc *scp, u_char *event)
{
	int ret;

	ret = 0;
	mtx_assert(&scp->seq_lock, MA_OWNED);

	SEQ_DEBUG(5, printf("seq_local: unit %d, cmd %d\n", scp->unit,
	    event[1]));
	switch (event[1]) {
	default:
		SEQ_DEBUG(1, printf("seq_local event type %d not handled\n",
		    event[1]));
		ret = 1;
		break;
	}
	return ret;
}