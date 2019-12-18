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
struct ocs_softc {int /*<<< orphan*/  ramlog; int /*<<< orphan*/  hw_war_version; scalar_t__ config_tgt; scalar_t__ enable_tgt; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  M_OCS ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_debug_detach (struct ocs_softc*) ; 
 int /*<<< orphan*/  ocs_device_detach (struct ocs_softc*) ; 
 int /*<<< orphan*/  ocs_device_lock_free (struct ocs_softc*) ; 
 int /*<<< orphan*/  ocs_ramlog_free (struct ocs_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_release_bus (struct ocs_softc*) ; 
 int /*<<< orphan*/  ocs_scsi_tgt_del_device (struct ocs_softc*) ; 

__attribute__((used)) static int
ocs_pci_detach(device_t dev)
{
	struct ocs_softc	*ocs;

	ocs = (struct ocs_softc *)device_get_softc(dev);
	if (!ocs) {
		device_printf(dev, "no driver context?!?\n");
		return -1;
	}

	if (ocs->config_tgt && ocs->enable_tgt) {
		device_printf(dev, "can't detach with target mode enabled\n");
		return EBUSY;
	}

	ocs_device_detach(ocs);

	/*
	 * Workaround for OCS SCSI Transport quirk.
	 *
	 * CTL requires that target mode is disabled prior to unloading the
	 * driver (ie ocs->enable_tgt = FALSE), but once the target is disabled,
	 * the transport will not call ocs_scsi_tgt_del_device() which deallocates
	 * CAM resources. The workaround is to explicitly make the call here.
	 */
	if (ocs->config_tgt)
		ocs_scsi_tgt_del_device(ocs);
        
	/* free strdup created buffer.*/
	free(ocs->hw_war_version, M_OCS);

	ocs_device_lock_free(ocs);

	ocs_debug_detach(ocs);

	ocs_ramlog_free(ocs, ocs->ramlog);

	ocs_release_bus(ocs);

	return 0;
}