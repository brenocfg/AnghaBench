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
struct sbc_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxcreate (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
sbc_lockinit(struct sbc_softc *scp)
{
	scp->lock = snd_mtxcreate(device_get_nameunit(scp->dev),
	    "snd_sbc softc");
}