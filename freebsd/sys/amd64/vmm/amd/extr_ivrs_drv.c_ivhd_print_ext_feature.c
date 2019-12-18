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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  REG_BITS (int,int,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
ivhd_print_ext_feature(device_t dev, uint64_t ext_feature)
{
	uint32_t ext_low, ext_high;

	if (!ext_feature)
		return;

	ext_low = ext_feature;
	device_printf(dev, "Extended features[31:0]:%b "
		"HATS = 0x%x GATS = 0x%x "
		"GLXSup = 0x%x SmiFSup = 0x%x SmiFRC = 0x%x "
		"GAMSup = 0x%x DualPortLogSup = 0x%x DualEventLogSup = 0x%x\n",
		(int)ext_low,
		"\020"
		"\001PreFSup"
		"\002PPRSup"
		"\003<b2>"
		"\004NXSup"
		"\005GTSup"
		"\006<b5>"
		"\007IASup"
		"\008GASup"
		"\009HESup"
		"\010PCSup",
		REG_BITS(ext_low, 11, 10),
		REG_BITS(ext_low, 13, 12),
		REG_BITS(ext_low, 15, 14),
		REG_BITS(ext_low, 17, 16),
		REG_BITS(ext_low, 20, 18),
		REG_BITS(ext_low, 23, 21),
		REG_BITS(ext_low, 25, 24),
		REG_BITS(ext_low, 29, 28));

	ext_high = ext_feature >> 32;
	device_printf(dev, "Extended features[62:32]:%b "
		"Max PASID: 0x%x DevTblSegSup = 0x%x "
		"MarcSup = 0x%x\n",
		(int)(ext_high),
		"\020"
		"\006USSup"
		"\009PprOvrflwEarlySup"
		"\010PPRAutoRspSup"
		"\013BlKStopMrkSup"
		"\014PerfOptSup"
		"\015MsiCapMmioSup"
		"\017GIOSup"
		"\018HASup"
		"\019EPHSup"
		"\020AttrFWSup"
		"\021HDSup"
		"\023InvIotlbSup",
	    	REG_BITS(ext_high, 5, 0),
	    	REG_BITS(ext_high, 8, 7),
	    	REG_BITS(ext_high, 11, 10));
}