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
struct fsl_sata_channel {int /*<<< orphan*/  mtx; scalar_t__ oslots; int /*<<< orphan*/  sim; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRIBIO ; 
 struct fsl_sata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_sata_deinit (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  msleep (struct fsl_sata_channel*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
fsl_sata_suspend(device_t dev)
{
	struct fsl_sata_channel *ch = device_get_softc(dev);

	mtx_lock(&ch->mtx);
	xpt_freeze_simq(ch->sim, 1);
	while (ch->oslots)
		msleep(ch, &ch->mtx, PRIBIO, "fsl_satasusp", hz/100);
	fsl_sata_deinit(dev);
	mtx_unlock(&ch->mtx);
	return (0);
}