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
typedef  int /*<<< orphan*/  vm_memattr_t ;
struct ntb_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 struct ntb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 unsigned int intel_ntb_mw_count (int /*<<< orphan*/ ) ; 
 int intel_ntb_mw_set_wc_internal (struct ntb_softc*,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int intel_ntb_user_mw_to_idx (struct ntb_softc*,unsigned int) ; 

__attribute__((used)) static int
intel_ntb_mw_set_wc(device_t dev, unsigned idx, vm_memattr_t mode)
{
	struct ntb_softc *ntb = device_get_softc(dev);

	if (idx >= intel_ntb_mw_count(dev))
		return (EINVAL);

	idx = intel_ntb_user_mw_to_idx(ntb, idx);
	return (intel_ntb_mw_set_wc_internal(ntb, idx, mode));
}