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
struct TYPE_8__ {int pko_nxa; int undflw; } ;
struct TYPE_7__ {int ncb_nxa; } ;
union cvmx_gmxx_tx_int_en {scalar_t__ u64; TYPE_4__ s; TYPE_3__ cn38xx; } ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ en; } ;
struct TYPE_5__ {int mode; } ;
union cvmx_gmxx_inf_mode {TYPE_2__ s; TYPE_1__ cn52xx; int /*<<< orphan*/  u64; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_INF_MODE (int) ; 
 int /*<<< orphan*/  CVMX_GMXX_TX_INT_EN (int) ; 
 int /*<<< orphan*/  OCTEON_CN38XX ; 
 int /*<<< orphan*/  OCTEON_CN52XX ; 
 int /*<<< orphan*/  OCTEON_CN56XX ; 
 int /*<<< orphan*/  OCTEON_CN58XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_interrupt_gmxx_rxx_int_en_enable (int,int) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 

void __cvmx_interrupt_gmxx_enable(int interface)
{
	union cvmx_gmxx_inf_mode mode;
	union cvmx_gmxx_tx_int_en gmx_tx_int_en;
	int num_ports;
	int index;

	mode.u64 = cvmx_read_csr(CVMX_GMXX_INF_MODE(interface));

	if (OCTEON_IS_MODEL(OCTEON_CN56XX) || OCTEON_IS_MODEL(OCTEON_CN52XX)) {
		if (mode.s.en) {
			switch (mode.cn52xx.mode) {
			case 1: /* XAUI */
				num_ports = 1;
				break;
			case 2: /* SGMII */
			case 3: /* PICMG */
				num_ports = 4;
				break;
			default:	/* Disabled */
				num_ports = 0;
				break;
			}
		} else
			num_ports = 0;
	} else {
		if (mode.s.en) {
			if (OCTEON_IS_MODEL(OCTEON_CN38XX)
			    || OCTEON_IS_MODEL(OCTEON_CN58XX)) {
				/*
				 * SPI on CN38XX and CN58XX report all
				 * errors through port 0.  RGMII needs
				 * to check all 4 ports
				 */
				if (mode.s.type)
					num_ports = 1;
				else
					num_ports = 4;
			} else {
				/*
				 * CN30XX, CN31XX, and CN50XX have two
				 * or three ports. GMII and MII has 2,
				 * RGMII has three
				 */
				if (mode.s.type)
					num_ports = 2;
				else
					num_ports = 3;
			}
		} else
			num_ports = 0;
	}

	gmx_tx_int_en.u64 = 0;
	if (num_ports) {
		if (OCTEON_IS_MODEL(OCTEON_CN38XX)
		    || OCTEON_IS_MODEL(OCTEON_CN58XX))
			gmx_tx_int_en.cn38xx.ncb_nxa = 1;
		gmx_tx_int_en.s.pko_nxa = 1;
	}
	gmx_tx_int_en.s.undflw = (1 << num_ports) - 1;
	cvmx_write_csr(CVMX_GMXX_TX_INT_EN(interface), gmx_tx_int_en.u64);
	for (index = 0; index < num_ports; index++)
		__cvmx_interrupt_gmxx_rxx_int_en_enable(index, interface);
}