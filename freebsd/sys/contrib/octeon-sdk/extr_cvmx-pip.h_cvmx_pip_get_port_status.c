#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_67__   TYPE_9__ ;
typedef  struct TYPE_66__   TYPE_8__ ;
typedef  struct TYPE_65__   TYPE_7__ ;
typedef  struct TYPE_64__   TYPE_6__ ;
typedef  struct TYPE_63__   TYPE_5__ ;
typedef  struct TYPE_62__   TYPE_4__ ;
typedef  struct TYPE_61__   TYPE_3__ ;
typedef  struct TYPE_60__   TYPE_33__ ;
typedef  struct TYPE_59__   TYPE_32__ ;
typedef  struct TYPE_58__   TYPE_31__ ;
typedef  struct TYPE_57__   TYPE_30__ ;
typedef  struct TYPE_56__   TYPE_2__ ;
typedef  struct TYPE_55__   TYPE_29__ ;
typedef  struct TYPE_54__   TYPE_28__ ;
typedef  struct TYPE_53__   TYPE_27__ ;
typedef  struct TYPE_52__   TYPE_26__ ;
typedef  struct TYPE_51__   TYPE_25__ ;
typedef  struct TYPE_50__   TYPE_24__ ;
typedef  struct TYPE_49__   TYPE_23__ ;
typedef  struct TYPE_48__   TYPE_22__ ;
typedef  struct TYPE_47__   TYPE_21__ ;
typedef  struct TYPE_46__   TYPE_20__ ;
typedef  struct TYPE_45__   TYPE_1__ ;
typedef  struct TYPE_44__   TYPE_19__ ;
typedef  struct TYPE_43__   TYPE_18__ ;
typedef  struct TYPE_42__   TYPE_17__ ;
typedef  struct TYPE_41__   TYPE_16__ ;
typedef  struct TYPE_40__   TYPE_15__ ;
typedef  struct TYPE_39__   TYPE_14__ ;
typedef  struct TYPE_38__   TYPE_13__ ;
typedef  struct TYPE_37__   TYPE_12__ ;
typedef  struct TYPE_36__   TYPE_11__ ;
typedef  struct TYPE_35__   TYPE_10__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_38__ {int /*<<< orphan*/  pkts; } ;
struct TYPE_42__ {TYPE_13__ s; void* u64; } ;
typedef  TYPE_17__ cvmx_pip_stat_inb_pktsx_t ;
struct TYPE_39__ {int /*<<< orphan*/  octs; } ;
struct TYPE_43__ {TYPE_14__ s; void* u64; } ;
typedef  TYPE_18__ cvmx_pip_stat_inb_octsx_t ;
struct TYPE_40__ {int /*<<< orphan*/  errs; } ;
struct TYPE_44__ {TYPE_15__ s; void* u64; } ;
typedef  TYPE_19__ cvmx_pip_stat_inb_errsx_t ;
struct TYPE_41__ {int rdclr; } ;
struct TYPE_46__ {scalar_t__ u64; TYPE_16__ s; } ;
typedef  TYPE_20__ cvmx_pip_stat_ctl_t ;
struct TYPE_35__ {int /*<<< orphan*/  jabber; int /*<<< orphan*/  oversz; } ;
struct TYPE_47__ {TYPE_10__ s; void* u64; } ;
typedef  TYPE_21__ cvmx_pip_stat9_prtx_t ;
struct TYPE_67__ {int /*<<< orphan*/  frag; int /*<<< orphan*/  undersz; } ;
struct TYPE_48__ {TYPE_9__ s; void* u64; } ;
typedef  TYPE_22__ cvmx_pip_stat8_prtx_t ;
struct TYPE_66__ {int /*<<< orphan*/  fcs; int /*<<< orphan*/  h1519; } ;
struct TYPE_49__ {TYPE_8__ s; void* u64; } ;
typedef  TYPE_23__ cvmx_pip_stat7_prtx_t ;
struct TYPE_65__ {int /*<<< orphan*/  h1024to1518; int /*<<< orphan*/  h512to1023; } ;
struct TYPE_50__ {TYPE_7__ s; void* u64; } ;
typedef  TYPE_24__ cvmx_pip_stat6_prtx_t ;
struct TYPE_64__ {int /*<<< orphan*/  h256to511; int /*<<< orphan*/  h128to255; } ;
struct TYPE_51__ {TYPE_6__ s; void* u64; } ;
typedef  TYPE_25__ cvmx_pip_stat5_prtx_t ;
struct TYPE_63__ {int /*<<< orphan*/  h65to127; int /*<<< orphan*/  h64; } ;
struct TYPE_52__ {TYPE_5__ s; void* u64; } ;
typedef  TYPE_26__ cvmx_pip_stat4_prtx_t ;
struct TYPE_62__ {int /*<<< orphan*/  bcst; int /*<<< orphan*/  mcst; } ;
struct TYPE_53__ {TYPE_4__ s; void* u64; } ;
typedef  TYPE_27__ cvmx_pip_stat3_prtx_t ;
struct TYPE_61__ {int /*<<< orphan*/  pkts; int /*<<< orphan*/  raw; } ;
struct TYPE_54__ {TYPE_3__ s; void* u64; } ;
typedef  TYPE_28__ cvmx_pip_stat2_prtx_t ;
struct TYPE_56__ {int /*<<< orphan*/  octs; } ;
struct TYPE_55__ {TYPE_2__ s; void* u64; } ;
typedef  TYPE_29__ cvmx_pip_stat1_prtx_t ;
struct TYPE_37__ {int /*<<< orphan*/  bcast; int /*<<< orphan*/  mcast; } ;
struct TYPE_57__ {TYPE_12__ s; void* u64; } ;
typedef  TYPE_30__ cvmx_pip_stat11_x_t ;
struct TYPE_36__ {int /*<<< orphan*/  bcast; int /*<<< orphan*/  mcast; } ;
struct TYPE_58__ {TYPE_11__ s; void* u64; } ;
typedef  TYPE_31__ cvmx_pip_stat10_x_t ;
struct TYPE_45__ {int /*<<< orphan*/  drp_pkts; int /*<<< orphan*/  drp_octs; } ;
struct TYPE_59__ {TYPE_1__ s; void* u64; } ;
typedef  TYPE_32__ cvmx_pip_stat0_prtx_t ;
struct TYPE_60__ {int /*<<< orphan*/  inb_errors; int /*<<< orphan*/  inb_octets; int /*<<< orphan*/  inb_packets; int /*<<< orphan*/  bcast_l3_red_packets; int /*<<< orphan*/  mcast_l3_red_packets; int /*<<< orphan*/  bcast_l2_red_packets; int /*<<< orphan*/  mcast_l2_red_packets; int /*<<< orphan*/  oversize_crc_packets; int /*<<< orphan*/  oversize_packets; int /*<<< orphan*/  runt_crc_packets; int /*<<< orphan*/  runt_packets; int /*<<< orphan*/  fcs_align_err_packets; int /*<<< orphan*/  len_1519_max_packets; int /*<<< orphan*/  len_1024_1518_packets; int /*<<< orphan*/  len_512_1023_packets; int /*<<< orphan*/  len_256_511_packets; int /*<<< orphan*/  len_128_255_packets; int /*<<< orphan*/  len_65_127_packets; int /*<<< orphan*/  len_64_packets; int /*<<< orphan*/  broadcast_packets; int /*<<< orphan*/  multicast_packets; int /*<<< orphan*/  packets; int /*<<< orphan*/  pci_raw_packets; int /*<<< orphan*/  octets; int /*<<< orphan*/  dropped_packets; int /*<<< orphan*/  dropped_octets; } ;
typedef  TYPE_33__ cvmx_pip_port_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_PIP_STAT0_PRTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT0_X (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT10_PRTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT10_X (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT11_PRTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT11_X (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT1_PRTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT1_X (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT2_PRTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT2_X (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT3_PRTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT3_X (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT4_PRTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT4_X (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT5_PRTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT5_X (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT6_PRTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT6_X (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT7_PRTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT7_X (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT8_PRTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT8_X (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT9_PRTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT9_X (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT_CTL ; 
 int /*<<< orphan*/  CVMX_PIP_STAT_INB_ERRSX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT_INB_ERRS_PKNDX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT_INB_OCTSX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT_INB_OCTS_PKNDX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT_INB_PKTSX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_STAT_INB_PKTS_PKNDX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_XSTAT0_PRTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_XSTAT10_PRTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_XSTAT11_PRTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_XSTAT1_PRTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_XSTAT2_PRTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_XSTAT3_PRTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_XSTAT4_PRTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_XSTAT5_PRTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_XSTAT6_PRTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_XSTAT7_PRTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_XSTAT8_PRTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_XSTAT9_PRTX (int) ; 
 int /*<<< orphan*/  OCTEON_CN52XX ; 
 int /*<<< orphan*/  OCTEON_CN56XX ; 
 int /*<<< orphan*/  OCTEON_CN6XXX ; 
 int /*<<< orphan*/  OCTEON_CNF7XXX ; 
 int /*<<< orphan*/  OCTEON_FEATURE_PKND ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int cvmx_helper_get_interface_index_num (int) ; 
 int cvmx_helper_get_interface_num (int) ; 
 int cvmx_helper_get_pknd (int,int) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cvmx_pip_get_port_status(uint64_t port_num, uint64_t clear, cvmx_pip_port_status_t *status)
{
    cvmx_pip_stat_ctl_t pip_stat_ctl;
    cvmx_pip_stat0_prtx_t stat0;
    cvmx_pip_stat1_prtx_t stat1;
    cvmx_pip_stat2_prtx_t stat2;
    cvmx_pip_stat3_prtx_t stat3;
    cvmx_pip_stat4_prtx_t stat4;
    cvmx_pip_stat5_prtx_t stat5;
    cvmx_pip_stat6_prtx_t stat6;
    cvmx_pip_stat7_prtx_t stat7;
    cvmx_pip_stat8_prtx_t stat8;
    cvmx_pip_stat9_prtx_t stat9;
    cvmx_pip_stat10_x_t stat10;
    cvmx_pip_stat11_x_t stat11;
    cvmx_pip_stat_inb_pktsx_t pip_stat_inb_pktsx;
    cvmx_pip_stat_inb_octsx_t pip_stat_inb_octsx;
    cvmx_pip_stat_inb_errsx_t pip_stat_inb_errsx;
    int interface = cvmx_helper_get_interface_num(port_num);
    int index = cvmx_helper_get_interface_index_num(port_num);

    pip_stat_ctl.u64 = 0;
    pip_stat_ctl.s.rdclr = clear;
    cvmx_write_csr(CVMX_PIP_STAT_CTL, pip_stat_ctl.u64);

    if (octeon_has_feature(OCTEON_FEATURE_PKND))
    {
        int pknd = cvmx_helper_get_pknd(interface, index);
        /*
         * PIP_STAT_CTL[MODE] 0 means pkind.
         */
        stat0.u64 = cvmx_read_csr(CVMX_PIP_STAT0_X(pknd));
        stat1.u64 = cvmx_read_csr(CVMX_PIP_STAT1_X(pknd));
        stat2.u64 = cvmx_read_csr(CVMX_PIP_STAT2_X(pknd));
        stat3.u64 = cvmx_read_csr(CVMX_PIP_STAT3_X(pknd));
        stat4.u64 = cvmx_read_csr(CVMX_PIP_STAT4_X(pknd));
        stat5.u64 = cvmx_read_csr(CVMX_PIP_STAT5_X(pknd));
        stat6.u64 = cvmx_read_csr(CVMX_PIP_STAT6_X(pknd));
        stat7.u64 = cvmx_read_csr(CVMX_PIP_STAT7_X(pknd));
        stat8.u64 = cvmx_read_csr(CVMX_PIP_STAT8_X(pknd));
        stat9.u64 = cvmx_read_csr(CVMX_PIP_STAT9_X(pknd));
        stat10.u64 = cvmx_read_csr(CVMX_PIP_STAT10_X(pknd));
        stat11.u64 = cvmx_read_csr(CVMX_PIP_STAT11_X(pknd));
    }
    else 
    {
        if (port_num >= 40)
        {
            stat0.u64 = cvmx_read_csr(CVMX_PIP_XSTAT0_PRTX(port_num));
            stat1.u64 = cvmx_read_csr(CVMX_PIP_XSTAT1_PRTX(port_num));
            stat2.u64 = cvmx_read_csr(CVMX_PIP_XSTAT2_PRTX(port_num));
            stat3.u64 = cvmx_read_csr(CVMX_PIP_XSTAT3_PRTX(port_num));
            stat4.u64 = cvmx_read_csr(CVMX_PIP_XSTAT4_PRTX(port_num));
            stat5.u64 = cvmx_read_csr(CVMX_PIP_XSTAT5_PRTX(port_num));
            stat6.u64 = cvmx_read_csr(CVMX_PIP_XSTAT6_PRTX(port_num));
            stat7.u64 = cvmx_read_csr(CVMX_PIP_XSTAT7_PRTX(port_num));
            stat8.u64 = cvmx_read_csr(CVMX_PIP_XSTAT8_PRTX(port_num));
            stat9.u64 = cvmx_read_csr(CVMX_PIP_XSTAT9_PRTX(port_num));
            if (OCTEON_IS_MODEL(OCTEON_CN6XXX))
            {
                stat10.u64 = cvmx_read_csr(CVMX_PIP_XSTAT10_PRTX(port_num));
                stat11.u64 = cvmx_read_csr(CVMX_PIP_XSTAT11_PRTX(port_num));
            }
        }
        else
        {
            stat0.u64 = cvmx_read_csr(CVMX_PIP_STAT0_PRTX(port_num));
            stat1.u64 = cvmx_read_csr(CVMX_PIP_STAT1_PRTX(port_num));
            stat2.u64 = cvmx_read_csr(CVMX_PIP_STAT2_PRTX(port_num));
            stat3.u64 = cvmx_read_csr(CVMX_PIP_STAT3_PRTX(port_num));
            stat4.u64 = cvmx_read_csr(CVMX_PIP_STAT4_PRTX(port_num));
            stat5.u64 = cvmx_read_csr(CVMX_PIP_STAT5_PRTX(port_num));
            stat6.u64 = cvmx_read_csr(CVMX_PIP_STAT6_PRTX(port_num));
            stat7.u64 = cvmx_read_csr(CVMX_PIP_STAT7_PRTX(port_num));
            stat8.u64 = cvmx_read_csr(CVMX_PIP_STAT8_PRTX(port_num));
            stat9.u64 = cvmx_read_csr(CVMX_PIP_STAT9_PRTX(port_num));
            if (OCTEON_IS_MODEL(OCTEON_CN52XX)
                || OCTEON_IS_MODEL(OCTEON_CN56XX)
                || OCTEON_IS_MODEL(OCTEON_CN6XXX)
                || OCTEON_IS_MODEL(OCTEON_CNF7XXX))
            {
                stat10.u64 = cvmx_read_csr(CVMX_PIP_STAT10_PRTX(port_num));
                stat11.u64 = cvmx_read_csr(CVMX_PIP_STAT11_PRTX(port_num));
            }
        }
    }
    if (octeon_has_feature(OCTEON_FEATURE_PKND))
    {
        int pknd = cvmx_helper_get_pknd(interface, index);

        pip_stat_inb_pktsx.u64 = cvmx_read_csr(CVMX_PIP_STAT_INB_PKTS_PKNDX(pknd));
        pip_stat_inb_octsx.u64 = cvmx_read_csr(CVMX_PIP_STAT_INB_OCTS_PKNDX(pknd));
        pip_stat_inb_errsx.u64 = cvmx_read_csr(CVMX_PIP_STAT_INB_ERRS_PKNDX(pknd));
    }
    else
    {
        pip_stat_inb_pktsx.u64 = cvmx_read_csr(CVMX_PIP_STAT_INB_PKTSX(port_num));
        pip_stat_inb_octsx.u64 = cvmx_read_csr(CVMX_PIP_STAT_INB_OCTSX(port_num));
        pip_stat_inb_errsx.u64 = cvmx_read_csr(CVMX_PIP_STAT_INB_ERRSX(port_num));
    }

    status->dropped_octets          = stat0.s.drp_octs;
    status->dropped_packets         = stat0.s.drp_pkts;
    status->octets                  = stat1.s.octs;
    status->pci_raw_packets         = stat2.s.raw;
    status->packets                 = stat2.s.pkts;
    status->multicast_packets       = stat3.s.mcst;
    status->broadcast_packets       = stat3.s.bcst;
    status->len_64_packets          = stat4.s.h64;
    status->len_65_127_packets      = stat4.s.h65to127;
    status->len_128_255_packets     = stat5.s.h128to255;
    status->len_256_511_packets     = stat5.s.h256to511;
    status->len_512_1023_packets    = stat6.s.h512to1023;
    status->len_1024_1518_packets   = stat6.s.h1024to1518;
    status->len_1519_max_packets    = stat7.s.h1519;
    status->fcs_align_err_packets   = stat7.s.fcs;
    status->runt_packets            = stat8.s.undersz;
    status->runt_crc_packets        = stat8.s.frag;
    status->oversize_packets        = stat9.s.oversz;
    status->oversize_crc_packets    = stat9.s.jabber;
    if (OCTEON_IS_MODEL(OCTEON_CN52XX)
        || OCTEON_IS_MODEL(OCTEON_CN56XX)
        || OCTEON_IS_MODEL(OCTEON_CN6XXX)
        || OCTEON_IS_MODEL(OCTEON_CNF7XXX))
    {
        status->mcast_l2_red_packets        = stat10.s.mcast;
        status->bcast_l2_red_packets        = stat10.s.bcast;
        status->mcast_l3_red_packets        = stat11.s.mcast;
        status->bcast_l3_red_packets        = stat11.s.bcast;
    }
    status->inb_packets             = pip_stat_inb_pktsx.s.pkts;
    status->inb_octets              = pip_stat_inb_octsx.s.octs;
    status->inb_errors              = pip_stat_inb_errsx.s.errs;
}