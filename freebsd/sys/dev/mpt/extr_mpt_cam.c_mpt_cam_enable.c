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
struct mpt_softc {scalar_t__ is_spi; scalar_t__ is_sas; scalar_t__ is_fc; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MPT_LOCK (struct mpt_softc*) ; 
 int /*<<< orphan*/  MPT_UNLOCK (struct mpt_softc*) ; 
 scalar_t__ mpt_read_config_info_fc (struct mpt_softc*) ; 
 scalar_t__ mpt_read_config_info_sas (struct mpt_softc*) ; 
 scalar_t__ mpt_read_config_info_spi (struct mpt_softc*) ; 
 scalar_t__ mpt_set_initial_config_fc (struct mpt_softc*) ; 
 scalar_t__ mpt_set_initial_config_sas (struct mpt_softc*) ; 
 scalar_t__ mpt_set_initial_config_spi (struct mpt_softc*) ; 

__attribute__((used)) static int
mpt_cam_enable(struct mpt_softc *mpt)
{
	int error;

	MPT_LOCK(mpt);

	error = EIO;
	if (mpt->is_fc) {
		if (mpt_read_config_info_fc(mpt)) {
			goto out;
		}
		if (mpt_set_initial_config_fc(mpt)) {
			goto out;
		}
	} else if (mpt->is_sas) {
		if (mpt_read_config_info_sas(mpt)) {
			goto out;
		}
		if (mpt_set_initial_config_sas(mpt)) {
			goto out;
		}
	} else if (mpt->is_spi) {
		if (mpt_read_config_info_spi(mpt)) {
			goto out;
		}
		if (mpt_set_initial_config_spi(mpt)) {
			goto out;
		}
	}
	error = 0;

out:
	MPT_UNLOCK(mpt);
	return (error);
}