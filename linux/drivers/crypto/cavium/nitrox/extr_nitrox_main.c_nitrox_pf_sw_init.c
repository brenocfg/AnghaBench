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
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nitrox_common_sw_cleanup (struct nitrox_device*) ; 
 int nitrox_common_sw_init (struct nitrox_device*) ; 
 int nitrox_register_interrupts (struct nitrox_device*) ; 

__attribute__((used)) static int nitrox_pf_sw_init(struct nitrox_device *ndev)
{
	int err;

	err = nitrox_common_sw_init(ndev);
	if (err)
		return err;

	err = nitrox_register_interrupts(ndev);
	if (err)
		nitrox_common_sw_cleanup(ndev);

	return err;
}