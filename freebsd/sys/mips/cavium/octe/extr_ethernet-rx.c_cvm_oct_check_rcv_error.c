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
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_20__ {int err_code; } ;
struct TYPE_21__ {TYPE_7__ snoip; } ;
struct TYPE_18__ {int /*<<< orphan*/  ipprt; } ;
struct TYPE_17__ {int len; } ;
struct TYPE_19__ {TYPE_5__ cn38xx; TYPE_4__ s; } ;
struct TYPE_15__ {int addr; } ;
struct TYPE_16__ {TYPE_2__ s; } ;
struct TYPE_22__ {TYPE_8__ word2; TYPE_6__ word1; TYPE_3__ packet_ptr; } ;
typedef  TYPE_9__ cvmx_wqe_t ;
struct TYPE_14__ {scalar_t__ pre_chk; } ;
struct TYPE_13__ {TYPE_1__ s; int /*<<< orphan*/  u64; } ;
typedef  TYPE_10__ cvmx_gmxx_rxx_frm_ctl_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_RXX_FRM_CTL (int,int) ; 
 int /*<<< orphan*/  DEBUGPRINT (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ USE_10MBPS_PREAMBLE_WORKAROUND ; 
 int /*<<< orphan*/  cvm_oct_free_work (TYPE_9__*) ; 
 int cvmx_helper_get_interface_index_num (int /*<<< orphan*/ ) ; 
 int cvmx_helper_get_interface_num (int /*<<< orphan*/ ) ; 
 int* cvmx_phys_to_ptr (int) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cvm_oct_check_rcv_error(cvmx_wqe_t *work)
{
	if ((work->word2.snoip.err_code == 10) && (work->word1.s.len <= 64)) {
		/* Ignore length errors on min size packets. Some equipment
		   incorrectly pads packets to 64+4FCS instead of 60+4FCS.
		   Note these packets still get counted as frame errors. */
	} else
	if (USE_10MBPS_PREAMBLE_WORKAROUND && ((work->word2.snoip.err_code == 5) || (work->word2.snoip.err_code == 7))) {

		/* We received a packet with either an alignment error or a
		   FCS error. This may be signalling that we are running
		   10Mbps with GMXX_RXX_FRM_CTL[PRE_CHK} off. If this is the
		   case we need to parse the packet to determine if we can
		   remove a non spec preamble and generate a correct packet */
		int interface = cvmx_helper_get_interface_num(work->word1.cn38xx.ipprt);
		int index = cvmx_helper_get_interface_index_num(work->word1.cn38xx.ipprt);
		cvmx_gmxx_rxx_frm_ctl_t gmxx_rxx_frm_ctl;
		gmxx_rxx_frm_ctl.u64 = cvmx_read_csr(CVMX_GMXX_RXX_FRM_CTL(index, interface));
		if (gmxx_rxx_frm_ctl.s.pre_chk == 0) {

			uint8_t *ptr = cvmx_phys_to_ptr(work->packet_ptr.s.addr);
			int i = 0;

			while (i < work->word1.s.len-1) {
				if (*ptr != 0x55)
					break;
				ptr++;
				i++;
			}

			if (*ptr == 0xd5) {
				/*
				DEBUGPRINT("Port %d received 0xd5 preamble\n", work->word1.cn38xx.ipprt);
				*/
				work->packet_ptr.s.addr += i+1;
				work->word1.s.len -= i+5;
			} else
			if ((*ptr & 0xf) == 0xd) {
				/*
				DEBUGPRINT("Port %d received 0x?d preamble\n", work->word1.cn38xx.ipprt);
				*/
				work->packet_ptr.s.addr += i;
				work->word1.s.len -= i+4;
				for (i = 0; i < work->word1.s.len; i++) {
					*ptr = ((*ptr&0xf0)>>4) | ((*(ptr+1)&0xf)<<4);
					ptr++;
				}
			} else {
				DEBUGPRINT("Port %d unknown preamble, packet dropped\n", work->word1.cn38xx.ipprt);
				/*
				cvmx_helper_dump_packet(work);
				*/
				cvm_oct_free_work(work);
				return 1;
			}
		}
	} else {
		DEBUGPRINT("Port %d receive error code %d, packet dropped\n", work->word1.cn38xx.ipprt, work->word2.snoip.err_code);
		cvm_oct_free_work(work);
		return 1;
	}

	return 0;
}