#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {int inf_en; } ;
struct TYPE_19__ {void* u64; TYPE_2__ s; } ;
typedef  TYPE_6__ cvmx_stxx_com_ctl_t ;
struct TYPE_14__ {int inf_en; } ;
struct TYPE_20__ {void* u64; TYPE_1__ s; } ;
typedef  TYPE_7__ cvmx_srxx_com_ctl_t ;
typedef  int cvmx_spi_mode_t ;
struct TYPE_18__ {int cnt; } ;
struct TYPE_21__ {void* u64; TYPE_5__ s; } ;
typedef  TYPE_8__ cvmx_gmxx_rxx_jabber_t ;
struct TYPE_16__ {int len; } ;
struct TYPE_22__ {void* u64; TYPE_3__ s; } ;
typedef  TYPE_9__ cvmx_gmxx_rxx_frm_min_t ;
struct TYPE_17__ {int len; } ;
struct TYPE_12__ {void* u64; TYPE_4__ s; } ;
typedef  TYPE_10__ cvmx_gmxx_rxx_frm_max_t ;
struct TYPE_13__ {scalar_t__ board_type; } ;

/* Variables and functions */
 scalar_t__ CVMX_BOARD_TYPE_CUST_RADISYS_RSYS4GBE ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_FRM_MAX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_FRM_MIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_JABBER (int /*<<< orphan*/ ,int) ; 
 int CVMX_SPI_MODE_RX_HALFPLEX ; 
 int CVMX_SPI_MODE_TX_HALFPLEX ; 
 int /*<<< orphan*/  CVMX_SRXX_COM_CTL (int) ; 
 int /*<<< orphan*/  CVMX_STXX_COM_CTL (int) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 TYPE_11__* cvmx_sysinfo_get () ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 

int cvmx_spi_interface_up_cb(int interface, cvmx_spi_mode_t mode)
{
    cvmx_gmxx_rxx_frm_min_t gmxx_rxx_frm_min;
    cvmx_gmxx_rxx_frm_max_t gmxx_rxx_frm_max;
    cvmx_gmxx_rxx_jabber_t gmxx_rxx_jabber;

    if (mode & CVMX_SPI_MODE_RX_HALFPLEX) {
        cvmx_srxx_com_ctl_t srxx_com_ctl;
        srxx_com_ctl.u64 = cvmx_read_csr(CVMX_SRXX_COM_CTL(interface));
        srxx_com_ctl.s.inf_en = 1;
        cvmx_write_csr (CVMX_SRXX_COM_CTL(interface), srxx_com_ctl.u64);
        cvmx_dprintf ("SPI%d: Rx is now up\n", interface);
    }

    if (mode & CVMX_SPI_MODE_TX_HALFPLEX) {
        cvmx_stxx_com_ctl_t stxx_com_ctl;
        stxx_com_ctl.u64 = cvmx_read_csr(CVMX_STXX_COM_CTL(interface));
        stxx_com_ctl.s.inf_en = 1;
        cvmx_write_csr (CVMX_STXX_COM_CTL(interface), stxx_com_ctl.u64);
        cvmx_dprintf ("SPI%d: Tx is now up\n", interface);
    }

    gmxx_rxx_frm_min.u64 = 0;
    gmxx_rxx_frm_min.s.len = 64;
#ifdef OCTEON_VENDOR_RADISYS
    /*
     * Incoming packets on the RSYS4GBE have the FCS stripped.
     */
    if (cvmx_sysinfo_get()->board_type == CVMX_BOARD_TYPE_CUST_RADISYS_RSYS4GBE)
	    gmxx_rxx_frm_min.s.len -= 4;
#endif
    cvmx_write_csr(CVMX_GMXX_RXX_FRM_MIN(0,interface), gmxx_rxx_frm_min.u64);
    gmxx_rxx_frm_max.u64 = 0;
    gmxx_rxx_frm_max.s.len = 64*1024 - 4;
    cvmx_write_csr(CVMX_GMXX_RXX_FRM_MAX(0,interface), gmxx_rxx_frm_max.u64);
    gmxx_rxx_jabber.u64 = 0;
    gmxx_rxx_jabber.s.cnt = 64*1024 - 4;
    cvmx_write_csr(CVMX_GMXX_RXX_JABBER(0,interface), gmxx_rxx_jabber.u64);

    return 0;
}