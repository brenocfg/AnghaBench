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
struct fsl_sata_channel {int /*<<< orphan*/  mtx; int /*<<< orphan*/  sim; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 struct fsl_sata_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_sata_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_sata_reset (struct fsl_sata_channel*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fsl_sata_resume(device_t dev)
{
	struct fsl_sata_channel *ch = device_get_softc(dev);

	mtx_lock(&ch->mtx);
	fsl_sata_init(dev);
	fsl_sata_reset(ch);
	xpt_release_simq(ch->sim, TRUE);
	mtx_unlock(&ch->mtx);
	return (0);
}