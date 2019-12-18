#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int present; } ;
struct TYPE_7__ {int present; } ;
struct TYPE_6__ {int present; } ;
struct TYPE_9__ {TYPE_3__ ts_rng; TYPE_2__ ts_nand; TYPE_1__ ts_rtc; } ;
struct TYPE_10__ {TYPE_4__ supports; } ;

/* Variables and functions */
 TYPE_5__ ts78xx_fpga ; 
 int /*<<< orphan*/  ts78xx_ts_nand_unload () ; 
 int /*<<< orphan*/  ts78xx_ts_rng_unload () ; 
 int /*<<< orphan*/  ts78xx_ts_rtc_unload () ; 

__attribute__((used)) static int ts78xx_fpga_unload_devices(void)
{
	int ret = 0;

	if (ts78xx_fpga.supports.ts_rtc.present == 1)
		ts78xx_ts_rtc_unload();
	if (ts78xx_fpga.supports.ts_nand.present == 1)
		ts78xx_ts_nand_unload();
	if (ts78xx_fpga.supports.ts_rng.present == 1)
		ts78xx_ts_rng_unload();

	return ret;
}