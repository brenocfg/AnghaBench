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
typedef  int /*<<< orphan*/  u64 ;
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPS_PKT_MBOX_PF_VF_PFDATAX (int) ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void pf2vf_write_mbox(struct nitrox_device *ndev, u64 value,
				    int ring)
{
	u64 reg_addr;

	reg_addr = NPS_PKT_MBOX_PF_VF_PFDATAX(ring);
	nitrox_write_csr(ndev, reg_addr, value);
}