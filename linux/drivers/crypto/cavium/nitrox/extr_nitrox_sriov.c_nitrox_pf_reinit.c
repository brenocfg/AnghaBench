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
struct nitrox_device {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __NDEV_READY ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitrox_common_sw_cleanup (struct nitrox_device*) ; 
 int nitrox_common_sw_init (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_config_aqm_rings (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_config_pkt_input_rings (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_config_pkt_solicit_ports (struct nitrox_device*) ; 
 int nitrox_crypto_register () ; 
 int nitrox_register_interrupts (struct nitrox_device*) ; 

__attribute__((used)) static int nitrox_pf_reinit(struct nitrox_device *ndev)
{
	int err;

	/* allocate resources for PF */
	err = nitrox_common_sw_init(ndev);
	if (err)
		return err;

	err = nitrox_register_interrupts(ndev);
	if (err) {
		nitrox_common_sw_cleanup(ndev);
		return err;
	}

	/* configure the AQM queues */
	nitrox_config_aqm_rings(ndev);

	/* configure the packet queues */
	nitrox_config_pkt_input_rings(ndev);
	nitrox_config_pkt_solicit_ports(ndev);

	/* set device to ready state */
	atomic_set(&ndev->state, __NDEV_READY);

	/* register crypto algorithms */
	return nitrox_crypto_register();
}