#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  tag; int /*<<< orphan*/  tag_type; int /*<<< orphan*/  index; int /*<<< orphan*/  grp; } ;
struct TYPE_14__ {TYPE_4__ s_sstatus2; void* u64; } ;
typedef  TYPE_5__ cvmx_pow_tag_load_resp_t ;
struct TYPE_15__ {int /*<<< orphan*/  tag; int /*<<< orphan*/  tag_type; int /*<<< orphan*/  index; int /*<<< orphan*/  grp; } ;
typedef  TYPE_6__ cvmx_pow_tag_info_t ;
struct TYPE_11__ {int /*<<< orphan*/  tag; int /*<<< orphan*/  tag_type; int /*<<< orphan*/  index; int /*<<< orphan*/  grp; } ;
struct TYPE_16__ {TYPE_2__ s; void* u64; } ;
typedef  TYPE_7__ cvmx_pow_sl_tag_resp_t ;
struct TYPE_12__ {int is_io; int get_cur; void* coreid; int /*<<< orphan*/  did; void* mem_region; } ;
struct TYPE_10__ {int is_io; int opcode; void* coreid; int /*<<< orphan*/  did; void* mem_region; } ;
struct TYPE_17__ {scalar_t__ u64; TYPE_3__ sstatus; TYPE_1__ sstatus_cn68xx; } ;
typedef  TYPE_8__ cvmx_pow_load_addr_t ;

/* Variables and functions */
 void* CVMX_IO_SEG ; 
 int /*<<< orphan*/  CVMX_OCT_DID_TAG_TAG1 ; 
 int /*<<< orphan*/  CVMX_OCT_DID_TAG_TAG5 ; 
 int /*<<< orphan*/  OCTEON_FEATURE_CN68XX_WQE ; 
 void* cvmx_get_core_num () ; 
 void* cvmx_read_csr (scalar_t__) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline cvmx_pow_tag_info_t cvmx_pow_get_current_tag(void)
{
    cvmx_pow_load_addr_t load_addr;
    cvmx_pow_tag_info_t result;

    if (octeon_has_feature(OCTEON_FEATURE_CN68XX_WQE)) {
        cvmx_pow_sl_tag_resp_t load_resp;
        load_addr.u64 = 0;
        load_addr.sstatus_cn68xx.mem_region = CVMX_IO_SEG;
        load_addr.sstatus_cn68xx.is_io = 1;
        load_addr.sstatus_cn68xx.did = CVMX_OCT_DID_TAG_TAG5;
        load_addr.sstatus_cn68xx.coreid = cvmx_get_core_num();
        load_addr.sstatus_cn68xx.opcode = 3;
        load_resp.u64 = cvmx_read_csr(load_addr.u64);
        result.grp = load_resp.s.grp;
        result.index = load_resp.s.index;
        result.tag_type = load_resp.s.tag_type;
        result.tag = load_resp.s.tag;
    } else {
        cvmx_pow_tag_load_resp_t load_resp;
        load_addr.u64 = 0;
        load_addr.sstatus.mem_region = CVMX_IO_SEG;
        load_addr.sstatus.is_io = 1;
        load_addr.sstatus.did = CVMX_OCT_DID_TAG_TAG1;
        load_addr.sstatus.coreid = cvmx_get_core_num();
        load_addr.sstatus.get_cur = 1;
        load_resp.u64 = cvmx_read_csr(load_addr.u64);
        result.grp = load_resp.s_sstatus2.grp;
        result.index = load_resp.s_sstatus2.index;
        result.tag_type = load_resp.s_sstatus2.tag_type;
        result.tag = load_resp.s_sstatus2.tag;
    }
    return result;
}