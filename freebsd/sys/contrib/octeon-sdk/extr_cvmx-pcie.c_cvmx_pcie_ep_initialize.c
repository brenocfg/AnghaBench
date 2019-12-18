#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_44__   TYPE_9__ ;
typedef  struct TYPE_43__   TYPE_8__ ;
typedef  struct TYPE_42__   TYPE_7__ ;
typedef  struct TYPE_41__   TYPE_6__ ;
typedef  struct TYPE_40__   TYPE_5__ ;
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_22__ ;
typedef  struct TYPE_35__   TYPE_21__ ;
typedef  struct TYPE_34__   TYPE_20__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_19__ ;
typedef  struct TYPE_31__   TYPE_18__ ;
typedef  struct TYPE_30__   TYPE_17__ ;
typedef  struct TYPE_29__   TYPE_16__ ;
typedef  struct TYPE_28__   TYPE_15__ ;
typedef  struct TYPE_27__   TYPE_14__ ;
typedef  struct TYPE_26__   TYPE_13__ ;
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
struct TYPE_43__ {void* mrrs; } ;
struct TYPE_26__ {void* u64; TYPE_8__ s; } ;
typedef  TYPE_13__ cvmx_sli_s2m_portx_ctl_t ;
struct TYPE_25__ {scalar_t__ ba; } ;
struct TYPE_24__ {scalar_t__ ba; } ;
struct TYPE_23__ {int port; scalar_t__ rtype; scalar_t__ wtype; scalar_t__ esw; scalar_t__ esr; scalar_t__ nmerge; } ;
struct TYPE_27__ {void* u64; TYPE_12__ cn63xx; TYPE_11__ cn68xx; TYPE_10__ s; } ;
typedef  TYPE_14__ cvmx_sli_mem_access_subidx_t ;
struct TYPE_40__ {int ro_en; int ns_en; int ce_en; int nfe_en; int fe_en; int ur_en; void* mrrs; void* mps; } ;
struct TYPE_28__ {int u32; TYPE_5__ s; } ;
typedef  TYPE_15__ cvmx_pcieepx_cfg030_t ;
struct TYPE_44__ {int port; int nmerge; scalar_t__ ba; scalar_t__ row; scalar_t__ ror; scalar_t__ nsw; scalar_t__ nsr; scalar_t__ esw; scalar_t__ esr; } ;
struct TYPE_29__ {void* u64; TYPE_9__ s; } ;
typedef  TYPE_16__ cvmx_npei_mem_access_subidx_t ;
struct TYPE_33__ {scalar_t__ host_mode; } ;
struct TYPE_30__ {TYPE_1__ s; void* u64; } ;
typedef  TYPE_17__ cvmx_npei_ctl_status_t ;
struct TYPE_41__ {void* mrrs; void* mps; } ;
struct TYPE_31__ {void* u64; TYPE_6__ s; } ;
typedef  TYPE_18__ cvmx_npei_ctl_status2_t ;
struct TYPE_37__ {scalar_t__ prtmode; int host_mode; } ;
struct TYPE_32__ {TYPE_2__ s; void* u64; } ;
typedef  TYPE_19__ cvmx_mio_rst_ctlx_t ;
struct TYPE_42__ {int molr; void* mrrs; void* mps; } ;
struct TYPE_34__ {void* u64; TYPE_7__ s; } ;
typedef  TYPE_20__ cvmx_dpi_sli_prtx_cfg_t ;
struct TYPE_38__ {int txbypass; int txdeemph; int txmargin; } ;
struct TYPE_35__ {void* u64; TYPE_3__ s; } ;
typedef  TYPE_21__ cvmx_ciu_qlm1_t ;
struct TYPE_39__ {int txbypass; int txdeemph; int txmargin; } ;
struct TYPE_36__ {void* u64; TYPE_4__ s; } ;
typedef  TYPE_22__ cvmx_ciu_qlm0_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_QLM0 ; 
 int /*<<< orphan*/  CVMX_CIU_QLM1 ; 
 int /*<<< orphan*/  CVMX_DPI_SLI_PRTX_CFG (int) ; 
 int /*<<< orphan*/  CVMX_MIO_RST_CTLX (int) ; 
 int /*<<< orphan*/  CVMX_PCIEEPX_CFG001 (int) ; 
 int /*<<< orphan*/  CVMX_PCIEEPX_CFG030 (int) ; 
 int /*<<< orphan*/  CVMX_PEXP_NPEI_CTL_STATUS ; 
 int /*<<< orphan*/  CVMX_PEXP_NPEI_CTL_STATUS2 ; 
 int /*<<< orphan*/  CVMX_PEXP_NPEI_MEM_ACCESS_SUBIDX (int) ; 
 int /*<<< orphan*/  CVMX_PEXP_SLI_MEM_ACCESS_SUBIDX (int) ; 
 int /*<<< orphan*/  CVMX_PEXP_SLI_S2M_PORTX_CTL (int) ; 
 void* MPS_CN5XXX ; 
 void* MPS_CN6XXX ; 
 void* MRRS_CN5XXX ; 
 void* MRRS_CN6XXX ; 
 int /*<<< orphan*/  OCTEON_CN5XXX ; 
 int /*<<< orphan*/  OCTEON_CN61XX ; 
 int /*<<< orphan*/  OCTEON_CN63XX_PASS1_0 ; 
 int /*<<< orphan*/  OCTEON_CN68XX ; 
 int /*<<< orphan*/  OCTEON_FEATURE_NPEI ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int cvmx_pcie_cfgx_read (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_pcie_cfgx_write (int,int /*<<< orphan*/ ,int) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 

int cvmx_pcie_ep_initialize(int pcie_port)
{
    if (octeon_has_feature(OCTEON_FEATURE_NPEI))
    {
        cvmx_npei_ctl_status_t npei_ctl_status;
        npei_ctl_status.u64 = cvmx_read_csr(CVMX_PEXP_NPEI_CTL_STATUS);
        if (npei_ctl_status.s.host_mode)
            return -1;
    }
    else
    {
        cvmx_mio_rst_ctlx_t mio_rst_ctl;
        int ep_mode;
        mio_rst_ctl.u64 = cvmx_read_csr(CVMX_MIO_RST_CTLX(pcie_port));
        ep_mode = (OCTEON_IS_MODEL(OCTEON_CN61XX) ? (mio_rst_ctl.s.prtmode != 0) : mio_rst_ctl.s.host_mode);
        if (ep_mode)
            return -1;
    }

    /* CN63XX Pass 1.0 errata G-14395 requires the QLM De-emphasis be programmed */
    if (OCTEON_IS_MODEL(OCTEON_CN63XX_PASS1_0))
    {
        if (pcie_port)
        {
            cvmx_ciu_qlm1_t ciu_qlm;
            ciu_qlm.u64 = cvmx_read_csr(CVMX_CIU_QLM1);
            ciu_qlm.s.txbypass = 1;
            ciu_qlm.s.txdeemph = 5;
            ciu_qlm.s.txmargin = 0x17;
            cvmx_write_csr(CVMX_CIU_QLM1, ciu_qlm.u64);
        }
        else
        {
            cvmx_ciu_qlm0_t ciu_qlm;
            ciu_qlm.u64 = cvmx_read_csr(CVMX_CIU_QLM0);
            ciu_qlm.s.txbypass = 1;
            ciu_qlm.s.txdeemph = 5;
            ciu_qlm.s.txmargin = 0x17;
            cvmx_write_csr(CVMX_CIU_QLM0, ciu_qlm.u64);
        }
    }

    /* Enable bus master and memory */
    cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIEEPX_CFG001(pcie_port), 0x6);

    /* Max Payload Size (PCIE*_CFG030[MPS]) */
    /* Max Read Request Size (PCIE*_CFG030[MRRS]) */
    /* Relaxed-order, no-snoop enables (PCIE*_CFG030[RO_EN,NS_EN] */
    /* Error Message Enables (PCIE*_CFG030[CE_EN,NFE_EN,FE_EN,UR_EN]) */
    {
        cvmx_pcieepx_cfg030_t pcieepx_cfg030;
        pcieepx_cfg030.u32 = cvmx_pcie_cfgx_read(pcie_port, CVMX_PCIEEPX_CFG030(pcie_port));
        if (OCTEON_IS_MODEL(OCTEON_CN5XXX))
        {
            pcieepx_cfg030.s.mps = MPS_CN5XXX;
            pcieepx_cfg030.s.mrrs = MRRS_CN5XXX;
        }
        else
        {
            pcieepx_cfg030.s.mps = MPS_CN6XXX;
            pcieepx_cfg030.s.mrrs = MRRS_CN6XXX;
        }
        pcieepx_cfg030.s.ro_en = 1; /* Enable relaxed ordering. */
        pcieepx_cfg030.s.ns_en = 1; /* Enable no snoop. */
        pcieepx_cfg030.s.ce_en = 1; /* Correctable error reporting enable. */
        pcieepx_cfg030.s.nfe_en = 1; /* Non-fatal error reporting enable. */
        pcieepx_cfg030.s.fe_en = 1; /* Fatal error reporting enable. */
        pcieepx_cfg030.s.ur_en = 1; /* Unsupported request reporting enable. */
        cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIEEPX_CFG030(pcie_port), pcieepx_cfg030.u32);
    }

    if (octeon_has_feature(OCTEON_FEATURE_NPEI))
    {
        /* Max Payload Size (NPEI_CTL_STATUS2[MPS]) must match PCIE*_CFG030[MPS] */
        /* Max Read Request Size (NPEI_CTL_STATUS2[MRRS]) must not exceed PCIE*_CFG030[MRRS] */
        cvmx_npei_ctl_status2_t npei_ctl_status2;
        npei_ctl_status2.u64 = cvmx_read_csr(CVMX_PEXP_NPEI_CTL_STATUS2);
        npei_ctl_status2.s.mps = MPS_CN5XXX; /* Max payload size = 128 bytes (Limit of most PCs) */
        npei_ctl_status2.s.mrrs = MRRS_CN5XXX; /* Max read request size = 128 bytes for best Octeon DMA performance */
        cvmx_write_csr(CVMX_PEXP_NPEI_CTL_STATUS2, npei_ctl_status2.u64);
    }
    else
    {
        /* Max Payload Size (DPI_SLI_PRTX_CFG[MPS]) must match PCIE*_CFG030[MPS] */
        /* Max Read Request Size (DPI_SLI_PRTX_CFG[MRRS]) must not exceed PCIE*_CFG030[MRRS] */
        cvmx_dpi_sli_prtx_cfg_t prt_cfg;
        cvmx_sli_s2m_portx_ctl_t sli_s2m_portx_ctl;
        prt_cfg.u64 = cvmx_read_csr(CVMX_DPI_SLI_PRTX_CFG(pcie_port));
        prt_cfg.s.mps = MPS_CN6XXX;
        prt_cfg.s.mrrs = MRRS_CN6XXX;
        /* Max outstanding load request. */
        prt_cfg.s.molr = 32;
        cvmx_write_csr(CVMX_DPI_SLI_PRTX_CFG(pcie_port), prt_cfg.u64);

        sli_s2m_portx_ctl.u64 = cvmx_read_csr(CVMX_PEXP_SLI_S2M_PORTX_CTL(pcie_port));
        sli_s2m_portx_ctl.s.mrrs = MRRS_CN6XXX;
        cvmx_write_csr(CVMX_PEXP_SLI_S2M_PORTX_CTL(pcie_port), sli_s2m_portx_ctl.u64);
    }

    /* Setup Mem access SubDID 12 to access Host memory */
    if (octeon_has_feature(OCTEON_FEATURE_NPEI))
    {
        cvmx_npei_mem_access_subidx_t mem_access_subid;
        mem_access_subid.u64 = 0;
        mem_access_subid.s.port = pcie_port; /* Port the request is sent to. */
        mem_access_subid.s.nmerge = 1;  /* Merging is not allowed in this window. */
        mem_access_subid.s.esr = 0;     /* Endian-swap for Reads. */
        mem_access_subid.s.esw = 0;     /* Endian-swap for Writes. */
        mem_access_subid.s.nsr = 0;     /* Enable Snooping for Reads. Octeon doesn't care, but devices might want this more conservative setting */
        mem_access_subid.s.nsw = 0;     /* Enable Snoop for Writes. */
        mem_access_subid.s.ror = 0;     /* Disable Relaxed Ordering for Reads. */
        mem_access_subid.s.row = 0;     /* Disable Relaxed Ordering for Writes. */
        mem_access_subid.s.ba = 0;      /* PCIe Adddress Bits <63:34>. */
        cvmx_write_csr(CVMX_PEXP_NPEI_MEM_ACCESS_SUBIDX(12), mem_access_subid.u64);
    }
    else
    {
        cvmx_sli_mem_access_subidx_t mem_access_subid;
        mem_access_subid.u64 = 0;
        mem_access_subid.s.port = pcie_port; /* Port the request is sent to. */
        mem_access_subid.s.nmerge = 0;  /* Merging is allowed in this window. */
        mem_access_subid.s.esr = 0;     /* Endian-swap for Reads. */
        mem_access_subid.s.esw = 0;     /* Endian-swap for Writes. */
        mem_access_subid.s.wtype = 0;   /* "No snoop" and "Relaxed ordering" are not set */
        mem_access_subid.s.rtype = 0;   /* "No snoop" and "Relaxed ordering" are not set */
        /* PCIe Adddress Bits <63:34>. */
        if (OCTEON_IS_MODEL(OCTEON_CN68XX))
            mem_access_subid.cn68xx.ba = 0;
        else
            mem_access_subid.cn63xx.ba = 0;
        cvmx_write_csr(CVMX_PEXP_SLI_MEM_ACCESS_SUBIDX(12 + pcie_port*4), mem_access_subid.u64);
    }
    return 0;
}