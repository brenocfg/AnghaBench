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
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPS_PKT_IN_ERR_TYPE_ENA_W1S ; 
 int /*<<< orphan*/  NPS_PKT_IN_RERR_HI_ENA_W1S ; 
 int /*<<< orphan*/  NPS_PKT_IN_RERR_LO_ENA_W1S ; 
 int /*<<< orphan*/  NPS_PKT_SLC_ERR_TYPE_ENA_W1S ; 
 int /*<<< orphan*/  NPS_PKT_SLC_RERR_HI_ENA_W1S ; 
 int /*<<< orphan*/  NPS_PKT_SLC_RERR_LO_ENA_W1S ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static void enable_nps_pkt_interrupts(struct nitrox_device *ndev)
{
	/* NPS packet in ring interrupts */
	nitrox_write_csr(ndev, NPS_PKT_IN_RERR_LO_ENA_W1S, (~0ULL));
	nitrox_write_csr(ndev, NPS_PKT_IN_RERR_HI_ENA_W1S, (~0ULL));
	nitrox_write_csr(ndev, NPS_PKT_IN_ERR_TYPE_ENA_W1S, (~0ULL));
	/* NPS packet slc port interrupts */
	nitrox_write_csr(ndev, NPS_PKT_SLC_RERR_HI_ENA_W1S, (~0ULL));
	nitrox_write_csr(ndev, NPS_PKT_SLC_RERR_LO_ENA_W1S, (~0ULL));
	nitrox_write_csr(ndev, NPS_PKT_SLC_ERR_TYPE_ENA_W1S, (~0uLL));
}