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
struct vtscsi_softc {int vtscsi_flags; } ;

/* Variables and functions */
 int MAXPHYS ; 
 int MIN (int,int) ; 
 int PAGE_SIZE ; 
 int VIRTIO_MAX_INDIRECT ; 
 int VTSCSI_FLAG_INDIRECT ; 
 int VTSCSI_MIN_SEGMENTS ; 

__attribute__((used)) static int
vtscsi_maximum_segments(struct vtscsi_softc *sc, int seg_max)
{
	int nsegs;

	nsegs = VTSCSI_MIN_SEGMENTS;

	if (seg_max > 0) {
		nsegs += MIN(seg_max, MAXPHYS / PAGE_SIZE + 1);
		if (sc->vtscsi_flags & VTSCSI_FLAG_INDIRECT)
			nsegs = MIN(nsegs, VIRTIO_MAX_INDIRECT);
	} else
		nsegs += 1;

	return (nsegs);
}