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
typedef  size_t uint64_t ;
typedef  size_t u_int ;
struct g_bde_work {size_t offset; size_t ko; size_t length; size_t so; size_t kso; struct g_bde_softc* softc; } ;
struct g_bde_key {size_t zone_cont; size_t sectorsize; size_t zone_width; size_t media_width; size_t sector0; size_t sectorN; int /*<<< orphan*/ * lsector; scalar_t__ keyoffset; } ;
struct g_bde_softc {struct g_bde_key key; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 size_t DFLTPHYS ; 
 size_t G_BDE_MAXKEYS ; 
 size_t G_BDE_SKEYLEN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 size_t rounddown2 (int /*<<< orphan*/ ,size_t) ; 

void
g_bde_map_sector(struct g_bde_work *wp)
{

	u_int	zone, zoff, u, len;
	uint64_t ko;
	struct g_bde_softc *sc;
	struct g_bde_key *kp;

	sc = wp->softc;
	kp = &sc->key;

	/* find which zone and the offset in it */
	zone = wp->offset / kp->zone_cont;
	zoff = wp->offset % kp->zone_cont;

	/* Calculate the offset of the key in the key sector */
	wp->ko = (zoff / kp->sectorsize) * G_BDE_SKEYLEN;

	/* restrict length to that zone */
	len = kp->zone_cont - zoff;

	/* ... and in general */
	if (len > DFLTPHYS)
		len = DFLTPHYS;

	if (len < wp->length)
		wp->length = len;

	/* Find physical sector address */
	wp->so = zone * kp->zone_width + zoff;
	wp->so += kp->keyoffset;
	wp->so %= kp->media_width;
	if (wp->so + wp->length > kp->media_width)
		wp->length = kp->media_width - wp->so;
	wp->so += kp->sector0;

	/* The key sector is the last in this zone. */
	wp->kso = zone * kp->zone_width + kp->zone_cont;
	wp->kso += kp->keyoffset;
	wp->kso %= kp->media_width;
	wp->kso += kp->sector0; 

	/* Compensate for lock sectors */
	for (u = 0; u < G_BDE_MAXKEYS; u++) {
		/* Find the start of this lock sector */
		ko = rounddown2(kp->lsector[u], (uint64_t)kp->sectorsize);

		if (wp->kso >= ko)
			wp->kso += kp->sectorsize;

		if (wp->so >= ko) {
			/* lock sector before work packet */
			wp->so += kp->sectorsize;
		} else if ((wp->so + wp->length) > ko) {
			/* lock sector in work packet, truncate */
			wp->length = ko - wp->so;
		}
	}

#if 0
	printf("off %jd len %jd so %jd ko %jd kso %u\n",
	    (intmax_t)wp->offset,
	    (intmax_t)wp->length,
	    (intmax_t)wp->so,
	    (intmax_t)wp->kso,
	    wp->ko);
#endif
	KASSERT(wp->so + wp->length <= kp->sectorN,
	    ("wp->so (%jd) + wp->length (%jd) > EOM (%jd), offset = %jd",
	    (intmax_t)wp->so,
	    (intmax_t)wp->length,
	    (intmax_t)kp->sectorN,
	    (intmax_t)wp->offset));

	KASSERT(wp->kso + kp->sectorsize <= kp->sectorN,
	    ("wp->kso (%jd) + kp->sectorsize > EOM (%jd), offset = %jd",
	    (intmax_t)wp->kso,
	    (intmax_t)kp->sectorN,
	    (intmax_t)wp->offset));

	KASSERT(wp->so >= kp->sector0,
	    ("wp->so (%jd) < BOM (%jd), offset = %jd",
	    (intmax_t)wp->so,
	    (intmax_t)kp->sector0,
	    (intmax_t)wp->offset));

	KASSERT(wp->kso >= kp->sector0,
	    ("wp->kso (%jd) <BOM (%jd), offset = %jd",
	    (intmax_t)wp->kso,
	    (intmax_t)kp->sector0,
	    (intmax_t)wp->offset));
}