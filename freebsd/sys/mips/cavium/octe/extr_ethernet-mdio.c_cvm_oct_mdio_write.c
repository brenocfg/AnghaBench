#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ifnet {int dummy; } ;
struct TYPE_6__ {int dat; scalar_t__ pending; } ;
struct TYPE_7__ {scalar_t__ u64; TYPE_2__ s; } ;
typedef  TYPE_3__ cvmx_smi_wr_dat_t ;
struct TYPE_5__ {int phy_adr; int reg_adr; scalar_t__ phy_op; } ;
struct TYPE_8__ {scalar_t__ u64; TYPE_1__ s; } ;
typedef  TYPE_4__ cvmx_smi_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_SMI_CMD ; 
 int /*<<< orphan*/  CVMX_SMI_WR_DAT ; 
 int /*<<< orphan*/  MDIO_LOCK () ; 
 int /*<<< orphan*/  MDIO_UNLOCK () ; 
 scalar_t__ cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_wait (int) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 

void cvm_oct_mdio_write(struct ifnet *ifp, int phy_id, int location, int val)
{
	cvmx_smi_cmd_t          smi_cmd;
	cvmx_smi_wr_dat_t       smi_wr;

	MDIO_LOCK();
	smi_wr.u64 = 0;
	smi_wr.s.dat = val;
	cvmx_write_csr(CVMX_SMI_WR_DAT, smi_wr.u64);

	smi_cmd.u64 = 0;
	smi_cmd.s.phy_op = 0;
	smi_cmd.s.phy_adr = phy_id;
	smi_cmd.s.reg_adr = location;
	cvmx_write_csr(CVMX_SMI_CMD, smi_cmd.u64);

	do {
		cvmx_wait(1000);
		smi_wr.u64 = cvmx_read_csr(CVMX_SMI_WR_DAT);
	} while (smi_wr.s.pending);
	MDIO_UNLOCK();
}