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
typedef  scalar_t__ uint16_t ;
struct amd_ntb_softc {int /*<<< orphan*/  device; TYPE_1__* hw_info; } ;
struct TYPE_2__ {scalar_t__ db_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  amd_ntb_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ntb_db_event (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
amd_ntb_interrupt(struct amd_ntb_softc *ntb, uint16_t vec)
{
	if (vec < ntb->hw_info->db_count)
		ntb_db_event(ntb->device, vec);
	else
		amd_ntb_printf(0, "Invalid vector %d\n", vec);
}