#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_7__ {TYPE_1__* extent; } ;
struct TYPE_8__ {TYPE_2__ config; } ;
struct TYPE_9__ {int /*<<< orphan*/ ** io; TYPE_3__ sli; } ;
typedef  TYPE_4__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_io_t ;
struct TYPE_6__ {size_t* base; } ;

/* Variables and functions */
 size_t SLI_RSRC_FCOE_XRI ; 

ocs_hw_io_t *
ocs_hw_io_lookup(ocs_hw_t *hw, uint32_t xri)
{
	uint32_t ioindex;
	ioindex = xri - hw->sli.config.extent[SLI_RSRC_FCOE_XRI].base[0];
	return hw->io[ioindex];
}