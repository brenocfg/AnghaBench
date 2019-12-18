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
 int /*<<< orphan*/  NPS_PKT_MBOX_VF_PF_PFDATAX (int) ; 
 int /*<<< orphan*/  nitrox_read_csr (struct nitrox_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u64 pf2vf_read_mbox(struct nitrox_device *ndev, int ring)
{
	u64 reg_addr;

	reg_addr = NPS_PKT_MBOX_VF_PF_PFDATAX(ring);
	return nitrox_read_csr(ndev, reg_addr);
}