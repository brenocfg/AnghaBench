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
struct seq_softc {int /*<<< orphan*/  seq_lock; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
#define  EV_CHN_COMMON 131 
#define  EV_CHN_VOICE 130 
 int EV_SEQ_LOCAL ; 
#define  EV_SYSEX 129 
 int EV_TIMING ; 
 int /*<<< orphan*/  SEQ_DEBUG (int,int /*<<< orphan*/ ) ; 
#define  SEQ_MIDIPUTC 128 
 int SYNTH_WRITERAW (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int seq_chncommon (struct seq_softc*,int /*<<< orphan*/ ,int*) ; 
 int seq_chnvoice (struct seq_softc*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ seq_fetch_mid (struct seq_softc*,int,int /*<<< orphan*/ *) ; 
 int seq_local (struct seq_softc*,int*) ; 
 int seq_sysex (struct seq_softc*,int /*<<< orphan*/ ,int*) ; 
 int seq_timing (struct seq_softc*,int*) ; 

__attribute__((used)) static int
seq_processevent(struct seq_softc *scp, u_char *event)
{
	int ret;
	kobj_t m;

	ret = 0;

	if (event[0] == EV_SEQ_LOCAL)
		ret = seq_local(scp, event);
	else if (event[0] == EV_TIMING)
		ret = seq_timing(scp, event);
	else if (event[0] != EV_CHN_VOICE &&
		    event[0] != EV_CHN_COMMON &&
		    event[0] != EV_SYSEX &&
	    event[0] != SEQ_MIDIPUTC) {
		ret = 1;
		SEQ_DEBUG(2, printf("seq_processevent not known %d\n",
		    event[0]));
	} else if (seq_fetch_mid(scp, event[1], &m) != 0) {
		ret = 1;
		SEQ_DEBUG(2, printf("seq_processevent midi unit not found %d\n",
		    event[1]));
	} else
		switch (event[0]) {
		case EV_CHN_VOICE:
			ret = seq_chnvoice(scp, m, event);
			break;
		case EV_CHN_COMMON:
			ret = seq_chncommon(scp, m, event);
			break;
		case EV_SYSEX:
			ret = seq_sysex(scp, m, event);
			break;
		case SEQ_MIDIPUTC:
			mtx_unlock(&scp->seq_lock);
			ret = SYNTH_WRITERAW(m, &event[2], 1);
			mtx_lock(&scp->seq_lock);
			break;
		}
	return ret;
}