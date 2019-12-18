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
struct TYPE_2__ {int timeout; int /*<<< orphan*/  cbfcnp; scalar_t__ retry_count; int /*<<< orphan*/  flags; int /*<<< orphan*/  func_code; } ;
union ccb {TYPE_1__ ccb_h; } ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_OUT ; 
 int /*<<< orphan*/  mmcprobe_done ; 

__attribute__((used)) static inline void
init_standard_ccb(union ccb *ccb, uint32_t cmd)
{
	ccb->ccb_h.func_code = cmd;
	ccb->ccb_h.flags = CAM_DIR_OUT;
	ccb->ccb_h.retry_count = 0;
	ccb->ccb_h.timeout = 15 * 1000;
	ccb->ccb_h.cbfcnp = mmcprobe_done;
}