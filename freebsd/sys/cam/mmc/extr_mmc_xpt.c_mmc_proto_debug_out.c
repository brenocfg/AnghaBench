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
struct TYPE_2__ {scalar_t__ func_code; int /*<<< orphan*/  path; } ;
union ccb {TYPE_1__ ccb_h; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_CDB ; 
 scalar_t__ XPT_MMC_IO ; 

__attribute__((used)) static void
mmc_proto_debug_out(union ccb *ccb)
{
	if (ccb->ccb_h.func_code != XPT_MMC_IO)
		return;

	CAM_DEBUG(ccb->ccb_h.path,
	    CAM_DEBUG_CDB,("mmc_proto_debug_out\n"));
}