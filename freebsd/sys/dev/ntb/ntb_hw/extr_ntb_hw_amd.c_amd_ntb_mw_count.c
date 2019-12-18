#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct amd_ntb_softc {TYPE_1__* hw_info; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  mw_count; } ;

/* Variables and functions */
 struct amd_ntb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t
amd_ntb_mw_count(device_t dev)
{
	struct amd_ntb_softc *ntb = device_get_softc(dev);

	return (ntb->hw_info->mw_count);
}