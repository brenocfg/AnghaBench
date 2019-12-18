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
struct edma_softc {int device_id; } ;
struct edma_channel {int enabled; int mux_num; int mux_src; int mux_chn; } ;

/* Variables and functions */
 int NCHAN_PER_MUX ; 
 int /*<<< orphan*/  dmamux_configure (int,int,int,int) ; 
 struct edma_channel* edma_map ; 

__attribute__((used)) static int
channel_configure(struct edma_softc *sc, int mux_grp, int mux_src)
{
	struct edma_channel *ch;
	int channel_first;
	int mux_num;
	int chnum;
	int i;

	if ((sc->device_id == 0 && mux_grp == 1) ||	\
	    (sc->device_id == 1 && mux_grp == 0)) {
		channel_first = NCHAN_PER_MUX;
		mux_num = (sc->device_id * 2) + 1;
	} else {
		channel_first = 0;
		mux_num = sc->device_id * 2;
	}

	/* Take first unused eDMA channel */
	ch = NULL;
	for (i = channel_first; i < (channel_first + NCHAN_PER_MUX); i++) {
		ch = &edma_map[i];
		if (ch->enabled == 0) {
			break;
		}
		ch = NULL;
	}

	if (ch == NULL) {
		/* Can't find free channel */
		return (-1);
	}

	chnum = i;

	ch->enabled = 1;
	ch->mux_num = mux_num;
	ch->mux_src = mux_src;
	ch->mux_chn = (chnum - channel_first);	/* 0 to 15 */

	dmamux_configure(ch->mux_num, ch->mux_src, ch->mux_chn, 1);

	return (chnum);
}