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
typedef  int u32 ;
struct ata_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PDC_DIMM0_SPD_DEV_ADDRESS ; 
 int PDC_DIMM_SPD_SYSTEM_FREQ ; 
 scalar_t__ pdc20621_i2c_read (struct ata_host*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int pdc20621_detect_dimm(struct ata_host *host)
{
	u32 data = 0;
	if (pdc20621_i2c_read(host, PDC_DIMM0_SPD_DEV_ADDRESS,
			     PDC_DIMM_SPD_SYSTEM_FREQ, &data)) {
		if (data == 100)
			return 100;
	} else
		return 0;

	if (pdc20621_i2c_read(host, PDC_DIMM0_SPD_DEV_ADDRESS, 9, &data)) {
		if (data <= 0x75)
			return 133;
	} else
		return 0;

	return 0;
}