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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vpd_readstate {int bytesinval; int off; int val; int cksum; int /*<<< orphan*/  cfg; int /*<<< orphan*/  pcib; } ;

/* Variables and functions */
 int ENXIO ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_read_vpd_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vpd_nextbyte(struct vpd_readstate *vrs, uint8_t *data)
{
	uint32_t reg;
	uint8_t byte;

	if (vrs->bytesinval == 0) {
		if (pci_read_vpd_reg(vrs->pcib, vrs->cfg, vrs->off, &reg))
			return (ENXIO);
		vrs->val = le32toh(reg);
		vrs->off += 4;
		byte = vrs->val & 0xff;
		vrs->bytesinval = 3;
	} else {
		vrs->val = vrs->val >> 8;
		byte = vrs->val & 0xff;
		vrs->bytesinval--;
	}

	vrs->cksum += byte;
	*data = byte;
	return (0);
}