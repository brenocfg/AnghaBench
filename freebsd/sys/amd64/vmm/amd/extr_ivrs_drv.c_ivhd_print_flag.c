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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum IvrsType { ____Placeholder_IvrsType } IvrsType ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  IVRS_TYPE_HARDWARE_EFR 130 
#define  IVRS_TYPE_HARDWARE_LEGACY 129 
#define  IVRS_TYPE_HARDWARE_MIXED 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static void
ivhd_print_flag(device_t dev, enum IvrsType ivhd_type, uint8_t flag)
{
	/*
	 * IVHD lgeacy type has two extra high bits in flag which has
	 * been moved to EFR for non-legacy device.
	 */
	switch (ivhd_type) {
	case IVRS_TYPE_HARDWARE_LEGACY:
		device_printf(dev, "Flag:%b\n", flag,
			"\020"
			"\001HtTunEn"
			"\002PassPW"
			"\003ResPassPW"
			"\004Isoc"
			"\005IotlbSup"
			"\006Coherent"
			"\007PreFSup"
			"\008PPRSup");
		break;

	case IVRS_TYPE_HARDWARE_EFR:
	case IVRS_TYPE_HARDWARE_MIXED:
		device_printf(dev, "Flag:%b\n", flag,
			"\020"
			"\001HtTunEn"
			"\002PassPW"
			"\003ResPassPW"
			"\004Isoc"
			"\005IotlbSup"
			"\006Coherent");
		break;

	default:
		device_printf(dev, "Can't decode flag of ivhd type :0x%x\n",
			ivhd_type);
		break;
	}
}