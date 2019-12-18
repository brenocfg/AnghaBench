#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  void* uint64_t ;
struct TYPE_25__ {void* wqe_pool; } ;
struct TYPE_27__ {scalar_t__ u64; TYPE_6__ s; } ;
typedef  TYPE_8__ cvmx_ipd_wqe_fpa_queue_t ;
struct TYPE_24__ {void* back; } ;
struct TYPE_28__ {scalar_t__ u64; TYPE_5__ s; } ;
typedef  TYPE_9__ cvmx_ipd_second_next_ptr_back_t ;
struct TYPE_22__ {void* mb_size; } ;
struct TYPE_15__ {scalar_t__ u64; TYPE_3__ s; } ;
typedef  TYPE_10__ cvmx_ipd_packet_mbuff_size_t ;
typedef  int /*<<< orphan*/  cvmx_ipd_mode_t ;
struct TYPE_21__ {void* skip_sz; } ;
struct TYPE_16__ {scalar_t__ u64; TYPE_2__ s; } ;
typedef  TYPE_11__ cvmx_ipd_mbuff_not_first_skip_t ;
struct TYPE_26__ {void* pbp_en; int /*<<< orphan*/  opc_mode; } ;
struct TYPE_17__ {scalar_t__ u64; TYPE_7__ s; } ;
typedef  TYPE_12__ cvmx_ipd_ctl_status_t ;
struct TYPE_23__ {void* back; } ;
struct TYPE_18__ {scalar_t__ u64; TYPE_4__ s; } ;
typedef  TYPE_13__ cvmx_ipd_1st_next_ptr_back_t ;
struct TYPE_20__ {void* skip_sz; } ;
struct TYPE_19__ {scalar_t__ u64; TYPE_1__ s; } ;
typedef  TYPE_14__ cvmx_ipd_1st_mbuff_skip_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_IPD_1ST_MBUFF_SKIP ; 
 int /*<<< orphan*/  CVMX_IPD_1st_NEXT_PTR_BACK ; 
 int /*<<< orphan*/  CVMX_IPD_2nd_NEXT_PTR_BACK ; 
 int /*<<< orphan*/  CVMX_IPD_CTL_STATUS ; 
 int /*<<< orphan*/  CVMX_IPD_NOT_1ST_MBUFF_SKIP ; 
 int /*<<< orphan*/  CVMX_IPD_PACKET_MBUFF_SIZE ; 
 int /*<<< orphan*/  CVMX_IPD_WQE_FPA_QUEUE ; 
 scalar_t__ cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void cvmx_ipd_config(uint64_t mbuff_size,
                                   uint64_t first_mbuff_skip,
                                   uint64_t not_first_mbuff_skip,
                                   uint64_t first_back,
                                   uint64_t second_back,
                                   uint64_t wqe_fpa_pool,
                                   cvmx_ipd_mode_t cache_mode,
                                   uint64_t back_pres_enable_flag
                                  )
{
    cvmx_ipd_1st_mbuff_skip_t first_skip;
    cvmx_ipd_mbuff_not_first_skip_t not_first_skip;
    cvmx_ipd_packet_mbuff_size_t size;
    cvmx_ipd_1st_next_ptr_back_t first_back_struct;
    cvmx_ipd_second_next_ptr_back_t second_back_struct;
    cvmx_ipd_wqe_fpa_queue_t wqe_pool;
    cvmx_ipd_ctl_status_t ipd_ctl_reg;

    first_skip.u64 = 0;
    first_skip.s.skip_sz = first_mbuff_skip;
    cvmx_write_csr(CVMX_IPD_1ST_MBUFF_SKIP, first_skip.u64);

    not_first_skip.u64 = 0;
    not_first_skip.s.skip_sz = not_first_mbuff_skip;
    cvmx_write_csr(CVMX_IPD_NOT_1ST_MBUFF_SKIP, not_first_skip.u64);

    size.u64 = 0;
    size.s.mb_size = mbuff_size;
    cvmx_write_csr(CVMX_IPD_PACKET_MBUFF_SIZE, size.u64);

    first_back_struct.u64 = 0;
    first_back_struct.s.back = first_back;
    cvmx_write_csr(CVMX_IPD_1st_NEXT_PTR_BACK, first_back_struct.u64);

    second_back_struct.u64 = 0;
    second_back_struct.s.back = second_back;
    cvmx_write_csr(CVMX_IPD_2nd_NEXT_PTR_BACK,second_back_struct.u64);

    wqe_pool.u64 = 0;
    wqe_pool.s.wqe_pool = wqe_fpa_pool;
    cvmx_write_csr(CVMX_IPD_WQE_FPA_QUEUE, wqe_pool.u64);

    ipd_ctl_reg.u64 = cvmx_read_csr(CVMX_IPD_CTL_STATUS);
    ipd_ctl_reg.s.opc_mode = cache_mode;
    ipd_ctl_reg.s.pbp_en = back_pres_enable_flag;
    cvmx_write_csr(CVMX_IPD_CTL_STATUS, ipd_ctl_reg.u64);

    /* Note: the example RED code that used to be here has been moved to
        cvmx_helper_setup_red */
}