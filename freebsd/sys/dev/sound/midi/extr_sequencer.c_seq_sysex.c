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
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SEQ_DEBUG (int,int /*<<< orphan*/ ) ; 
 scalar_t__ SYNTH_SENDSYSEX (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static int
seq_sysex(struct seq_softc *scp, kobj_t md, u_char *event)
{
	int i, l;

	mtx_assert(&scp->seq_lock, MA_OWNED);
	SEQ_DEBUG(5, printf("seq_sysex: unit %d device %d\n", scp->unit,
	    event[1]));
	l = 0;
	for (i = 0; i < 6 && event[i + 2] != 0xff; i++)
		l = i + 1;
	if (l > 0) {
		mtx_unlock(&scp->seq_lock);
		if (SYNTH_SENDSYSEX(md, &event[2], l) == EAGAIN) {
			mtx_lock(&scp->seq_lock);
			return 1;
		}
		mtx_lock(&scp->seq_lock);
	}
	return 0;
}