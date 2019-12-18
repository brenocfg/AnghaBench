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
struct vtblk_softc {int vtblk_flags; int /*<<< orphan*/  vtblk_dev; } ;
struct virtio_blk_config {int writeback; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_BLK_F_WCE ; 
 int VTBLK_CACHE_MAX ; 
 int VTBLK_FLAG_WC_CONFIG ; 
 int virtio_with_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtblk_set_write_cache (struct vtblk_softc*,int) ; 
 int vtblk_tunable_int (struct vtblk_softc*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtblk_writecache_mode ; 

__attribute__((used)) static int
vtblk_write_cache_enabled(struct vtblk_softc *sc,
    struct virtio_blk_config *blkcfg)
{
	int wc;

	if (sc->vtblk_flags & VTBLK_FLAG_WC_CONFIG) {
		wc = vtblk_tunable_int(sc, "writecache_mode",
		    vtblk_writecache_mode);
		if (wc >= 0 && wc < VTBLK_CACHE_MAX)
			vtblk_set_write_cache(sc, wc);
		else
			wc = blkcfg->writeback;
	} else
		wc = virtio_with_feature(sc->vtblk_dev, VIRTIO_BLK_F_WCE);

	return (wc);
}