#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cvmx_wqe_t ;
struct TYPE_7__ {scalar_t__ inc_prt_flag; } ;
struct TYPE_10__ {TYPE_1__ s; void* u64; } ;
typedef  TYPE_4__ cvmx_pip_prt_tagx_t ;
struct TYPE_8__ {int tag; } ;
struct TYPE_11__ {TYPE_2__ s; void* u64; } ;
typedef  TYPE_5__ cvmx_pip_bsel_tbl_entx_t ;
struct TYPE_9__ {int upper_tag; int tag; } ;
struct TYPE_12__ {TYPE_3__ s; void* u64; } ;
typedef  TYPE_6__ cvmx_pip_bsel_ext_cfgx_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_PIP_BSEL_EXT_CFGX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_BSEL_TBL_ENTX (int) ; 
 int /*<<< orphan*/  CVMX_PIP_PRT_TAGX (int) ; 
 int /*<<< orphan*/  OCTEON_FEATURE_BIT_EXTRACTOR ; 
 int cvmx_pip_get_bsel_table_index (int /*<<< orphan*/ *) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int cvmx_wqe_get_port (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  octeon_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cvmx_pip_get_bsel_tag(cvmx_wqe_t *work)
{
    int index = cvmx_pip_get_bsel_table_index(work);
    int port = cvmx_wqe_get_port(work);
    int bit = port & 0x3;
    int upper_tag = 0;
    cvmx_pip_bsel_tbl_entx_t bsel_tbl;
    cvmx_pip_bsel_ext_cfgx_t bsel_cfg;
    cvmx_pip_prt_tagx_t prt_tag;

    /* The bit select extractor is available in CN61XX and CN68XX pass2.0 onwards. */
    if (!octeon_has_feature(OCTEON_FEATURE_BIT_EXTRACTOR))
        return -1;

    bsel_tbl.u64 = cvmx_read_csr(CVMX_PIP_BSEL_TBL_ENTX(index));
    bsel_cfg.u64 = cvmx_read_csr(CVMX_PIP_BSEL_EXT_CFGX(bit));

    prt_tag.u64 = cvmx_read_csr(CVMX_PIP_PRT_TAGX(port));
    if (prt_tag.s.inc_prt_flag == 0) 
        upper_tag = bsel_cfg.s.upper_tag;
    return (bsel_tbl.s.tag | ((bsel_cfg.s.tag << 8) & 0xff00) | ((upper_tag << 16) & 0xffff0000));
}