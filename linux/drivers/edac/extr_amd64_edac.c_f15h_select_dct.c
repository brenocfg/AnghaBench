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
typedef  int u8 ;
typedef  int u32 ;
struct amd64_pvt {int model; int /*<<< orphan*/  F1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCT_CFG_SEL ; 
 int /*<<< orphan*/  amd64_read_pci_cfg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  amd64_write_pci_cfg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void f15h_select_dct(struct amd64_pvt *pvt, u8 dct)
{
	u32 reg = 0;

	amd64_read_pci_cfg(pvt->F1, DCT_CFG_SEL, &reg);
	reg &= (pvt->model == 0x30) ? ~3 : ~1;
	reg |= dct;
	amd64_write_pci_cfg(pvt->F1, DCT_CFG_SEL, reg);
}