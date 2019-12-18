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
struct g_raid_volume {scalar_t__ v_mediasize; int /*<<< orphan*/  v_sectorsize; } ;
struct g_raid_softc {int dummy; } ;
struct g_provider {int /*<<< orphan*/  name; struct g_raid_volume* private; } ;
struct TYPE_2__ {scalar_t__ mediaoffset; scalar_t__ mediasize; int /*<<< orphan*/  maxiosize; int /*<<< orphan*/  blocksize; struct g_raid_volume* priv; int /*<<< orphan*/  dumper; } ;
struct g_kerneldump {scalar_t__ offset; scalar_t__ length; TYPE_1__ di; } ;
struct bio {struct g_provider* bio_to; scalar_t__ bio_data; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  DFLTPHYS ; 
 int /*<<< orphan*/  G_T_TOPOLOGY ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid_dump ; 
 int /*<<< orphan*/  g_trace (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_raid_kerneldump(struct g_raid_softc *sc, struct bio *bp)
{
	struct g_kerneldump *gkd;
	struct g_provider *pp;
	struct g_raid_volume *vol;

	gkd = (struct g_kerneldump*)bp->bio_data;
	pp = bp->bio_to;
	vol = pp->private;
	g_trace(G_T_TOPOLOGY, "g_raid_kerneldump(%s, %jd, %jd)",
		pp->name, (intmax_t)gkd->offset, (intmax_t)gkd->length);
	gkd->di.dumper = g_raid_dump;
	gkd->di.priv = vol;
	gkd->di.blocksize = vol->v_sectorsize;
	gkd->di.maxiosize = DFLTPHYS;
	gkd->di.mediaoffset = gkd->offset;
	if ((gkd->offset + gkd->length) > vol->v_mediasize)
		gkd->length = vol->v_mediasize - gkd->offset;
	gkd->di.mediasize = gkd->length;
	g_io_deliver(bp, 0);
}