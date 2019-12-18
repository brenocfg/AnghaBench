#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_60__   TYPE_9__ ;
typedef  struct TYPE_59__   TYPE_8__ ;
typedef  struct TYPE_58__   TYPE_7__ ;
typedef  struct TYPE_57__   TYPE_6__ ;
typedef  struct TYPE_56__   TYPE_5__ ;
typedef  struct TYPE_55__   TYPE_4__ ;
typedef  struct TYPE_54__   TYPE_3__ ;
typedef  struct TYPE_53__   TYPE_30__ ;
typedef  struct TYPE_52__   TYPE_2__ ;
typedef  struct TYPE_51__   TYPE_29__ ;
typedef  struct TYPE_50__   TYPE_28__ ;
typedef  struct TYPE_49__   TYPE_27__ ;
typedef  struct TYPE_48__   TYPE_26__ ;
typedef  struct TYPE_47__   TYPE_25__ ;
typedef  struct TYPE_46__   TYPE_24__ ;
typedef  struct TYPE_45__   TYPE_23__ ;
typedef  struct TYPE_44__   TYPE_22__ ;
typedef  struct TYPE_43__   TYPE_21__ ;
typedef  struct TYPE_42__   TYPE_20__ ;
typedef  struct TYPE_41__   TYPE_1__ ;
typedef  struct TYPE_40__   TYPE_19__ ;
typedef  struct TYPE_39__   TYPE_18__ ;
typedef  struct TYPE_38__   TYPE_17__ ;
typedef  struct TYPE_37__   TYPE_16__ ;
typedef  struct TYPE_36__   TYPE_15__ ;
typedef  struct TYPE_35__   TYPE_14__ ;
typedef  struct TYPE_34__   TYPE_13__ ;
typedef  struct TYPE_33__   TYPE_12__ ;
typedef  struct TYPE_32__   TYPE_11__ ;
typedef  struct TYPE_31__   TYPE_10__ ;

/* Type definitions */
struct TYPE_58__ {void* mrrs; } ;
struct TYPE_37__ {void* u64; TYPE_7__ s; } ;
typedef  TYPE_16__ cvmx_sli_s2m_portx_ctl_t ;
struct TYPE_52__ {int cere; int nfere; int fere; } ;
struct TYPE_38__ {void* u32; TYPE_2__ s; } ;
typedef  TYPE_17__ cvmx_pciercx_cfg075_t ;
struct TYPE_59__ {int ge; int ce; } ;
struct TYPE_39__ {void* u32; TYPE_8__ s; } ;
typedef  TYPE_18__ cvmx_pciercx_cfg070_t ;
struct TYPE_41__ {int secee; int sefee; int senfee; int pmeie; } ;
struct TYPE_40__ {void* u32; TYPE_1__ s; } ;
typedef  TYPE_19__ cvmx_pciercx_cfg035_t ;
struct TYPE_54__ {int hpint_en; int dlls_en; int ccint_en; } ;
struct TYPE_42__ {void* u32; TYPE_3__ s; } ;
typedef  TYPE_20__ cvmx_pciercx_cfg034_t ;
struct TYPE_31__ {scalar_t__ aslpc; } ;
struct TYPE_43__ {void* u32; TYPE_10__ s; } ;
typedef  TYPE_21__ cvmx_pciercx_cfg032_t ;
struct TYPE_55__ {int ro_en; int ns_en; int ce_en; int nfe_en; int fe_en; int ur_en; void* mrrs; void* mps; } ;
struct TYPE_44__ {void* u32; TYPE_4__ s; } ;
typedef  TYPE_22__ cvmx_pciercx_cfg030_t ;
struct TYPE_36__ {scalar_t__ umem_limit; } ;
struct TYPE_45__ {void* u32; TYPE_15__ s; } ;
typedef  TYPE_23__ cvmx_pciercx_cfg011_t ;
struct TYPE_35__ {int umem_base; } ;
struct TYPE_46__ {void* u32; TYPE_14__ s; } ;
typedef  TYPE_24__ cvmx_pciercx_cfg010_t ;
struct TYPE_34__ {int lmem_base; scalar_t__ lmem_limit; } ;
struct TYPE_47__ {void* u32; TYPE_13__ s; } ;
typedef  TYPE_25__ cvmx_pciercx_cfg009_t ;
struct TYPE_33__ {int mb_addr; scalar_t__ ml_addr; } ;
struct TYPE_48__ {void* u32; TYPE_12__ s; } ;
typedef  TYPE_26__ cvmx_pciercx_cfg008_t ;
struct TYPE_32__ {int pbnum; int sbnum; int subbnum; } ;
struct TYPE_49__ {void* u32; TYPE_11__ s; } ;
typedef  TYPE_27__ cvmx_pciercx_cfg006_t ;
struct TYPE_60__ {int msae; int me; int i_dis; int see; } ;
struct TYPE_50__ {void* u32; TYPE_9__ s; } ;
typedef  TYPE_28__ cvmx_pciercx_cfg001_t ;
struct TYPE_56__ {int c1_b1_s; int c0_b1_s; void* mrrs; void* mps; } ;
struct TYPE_51__ {void* u64; TYPE_5__ s; } ;
typedef  TYPE_29__ cvmx_npei_ctl_status2_t ;
struct TYPE_57__ {int molr; void* mrrs; void* mps; } ;
struct TYPE_53__ {void* u64; TYPE_6__ s; } ;
typedef  TYPE_30__ cvmx_dpi_sli_prtx_cfg_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_DPI_SLI_PRTX_CFG (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG001 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG006 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG008 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG009 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG010 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG011 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG030 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG032 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG034 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG035 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG066 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG069 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG070 (int) ; 
 int /*<<< orphan*/  CVMX_PCIERCX_CFG075 (int) ; 
 int /*<<< orphan*/  CVMX_PEXP_NPEI_CTL_STATUS2 ; 
 int /*<<< orphan*/  CVMX_PEXP_SLI_S2M_PORTX_CTL (int) ; 
 void* MPS_CN5XXX ; 
 void* MPS_CN6XXX ; 
 void* MRRS_CN5XXX ; 
 void* MRRS_CN6XXX ; 
 int /*<<< orphan*/  OCTEON_CN5XXX ; 
 int /*<<< orphan*/  OCTEON_FEATURE_NPEI ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 void* cvmx_pcie_cfgx_read (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_pcie_cfgx_write (int,int /*<<< orphan*/ ,void*) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __cvmx_pcie_rc_initialize_config_space(int pcie_port)
{
    /* Max Payload Size (PCIE*_CFG030[MPS]) */
    /* Max Read Request Size (PCIE*_CFG030[MRRS]) */
    /* Relaxed-order, no-snoop enables (PCIE*_CFG030[RO_EN,NS_EN] */
    /* Error Message Enables (PCIE*_CFG030[CE_EN,NFE_EN,FE_EN,UR_EN]) */
    {
        cvmx_pciercx_cfg030_t pciercx_cfg030;
        pciercx_cfg030.u32 = cvmx_pcie_cfgx_read(pcie_port, CVMX_PCIERCX_CFG030(pcie_port));
        if (OCTEON_IS_MODEL(OCTEON_CN5XXX))
        {
            pciercx_cfg030.s.mps = MPS_CN5XXX;
            pciercx_cfg030.s.mrrs = MRRS_CN5XXX;
        }
        else
        {
            pciercx_cfg030.s.mps = MPS_CN6XXX;
            pciercx_cfg030.s.mrrs = MRRS_CN6XXX;
        }
        pciercx_cfg030.s.ro_en = 1; /* Enable relaxed order processing. This will allow devices to affect read response ordering */
        pciercx_cfg030.s.ns_en = 1; /* Enable no snoop processing. Not used by Octeon */
        pciercx_cfg030.s.ce_en = 1; /* Correctable error reporting enable. */
        pciercx_cfg030.s.nfe_en = 1; /* Non-fatal error reporting enable. */
        pciercx_cfg030.s.fe_en = 1; /* Fatal error reporting enable. */
        pciercx_cfg030.s.ur_en = 1; /* Unsupported request reporting enable. */
        cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG030(pcie_port), pciercx_cfg030.u32);
    }

    if (octeon_has_feature(OCTEON_FEATURE_NPEI))
    {
        /* Max Payload Size (NPEI_CTL_STATUS2[MPS]) must match PCIE*_CFG030[MPS] */
        /* Max Read Request Size (NPEI_CTL_STATUS2[MRRS]) must not exceed PCIE*_CFG030[MRRS] */
        cvmx_npei_ctl_status2_t npei_ctl_status2;
        npei_ctl_status2.u64 = cvmx_read_csr(CVMX_PEXP_NPEI_CTL_STATUS2);
        npei_ctl_status2.s.mps = MPS_CN5XXX; /* Max payload size = 128 bytes for best Octeon DMA performance */
        npei_ctl_status2.s.mrrs = MRRS_CN5XXX; /* Max read request size = 128 bytes for best Octeon DMA performance */
        if (pcie_port)
            npei_ctl_status2.s.c1_b1_s = 3; /* Port1 BAR1 Size 256MB */
        else
            npei_ctl_status2.s.c0_b1_s = 3; /* Port0 BAR1 Size 256MB */

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

    /* ECRC Generation (PCIE*_CFG070[GE,CE]) */
    {
        cvmx_pciercx_cfg070_t pciercx_cfg070;
        pciercx_cfg070.u32 = cvmx_pcie_cfgx_read(pcie_port, CVMX_PCIERCX_CFG070(pcie_port));
        pciercx_cfg070.s.ge = 1; /* ECRC generation enable. */
        pciercx_cfg070.s.ce = 1; /* ECRC check enable. */
        cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG070(pcie_port), pciercx_cfg070.u32);
    }

    /* Access Enables (PCIE*_CFG001[MSAE,ME]) */
        /* ME and MSAE should always be set. */
    /* Interrupt Disable (PCIE*_CFG001[I_DIS]) */
    /* System Error Message Enable (PCIE*_CFG001[SEE]) */
    {
        cvmx_pciercx_cfg001_t pciercx_cfg001;
        pciercx_cfg001.u32 = cvmx_pcie_cfgx_read(pcie_port, CVMX_PCIERCX_CFG001(pcie_port));
        pciercx_cfg001.s.msae = 1; /* Memory space enable. */
        pciercx_cfg001.s.me = 1; /* Bus master enable. */
        pciercx_cfg001.s.i_dis = 1; /* INTx assertion disable. */
        pciercx_cfg001.s.see = 1; /* SERR# enable */
        cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG001(pcie_port), pciercx_cfg001.u32);
    }


    /* Advanced Error Recovery Message Enables */
    /* (PCIE*_CFG066,PCIE*_CFG067,PCIE*_CFG069) */
    cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG066(pcie_port), 0);
    /* Use CVMX_PCIERCX_CFG067 hardware default */
    cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG069(pcie_port), 0);


    /* Active State Power Management (PCIE*_CFG032[ASLPC]) */
    {
        cvmx_pciercx_cfg032_t pciercx_cfg032;
        pciercx_cfg032.u32 = cvmx_pcie_cfgx_read(pcie_port, CVMX_PCIERCX_CFG032(pcie_port));
        pciercx_cfg032.s.aslpc = 0; /* Active state Link PM control. */
        cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG032(pcie_port), pciercx_cfg032.u32);
    }

    /* Link Width Mode (PCIERCn_CFG452[LME]) - Set during cvmx_pcie_rc_initialize_link() */
    /* Primary Bus Number (PCIERCn_CFG006[PBNUM]) */
    {
        /* We set the primary bus number to 1 so IDT bridges are happy. They don't like zero */
        cvmx_pciercx_cfg006_t pciercx_cfg006;
        pciercx_cfg006.u32 = 0;
        pciercx_cfg006.s.pbnum = 1;
        pciercx_cfg006.s.sbnum = 1;
        pciercx_cfg006.s.subbnum = 1;
        cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG006(pcie_port), pciercx_cfg006.u32);
    }

    /* Memory-mapped I/O BAR (PCIERCn_CFG008) */
    /* Most applications should disable the memory-mapped I/O BAR by */
    /* setting PCIERCn_CFG008[ML_ADDR] < PCIERCn_CFG008[MB_ADDR] */
    {
        cvmx_pciercx_cfg008_t pciercx_cfg008;
        pciercx_cfg008.u32 = 0;
        pciercx_cfg008.s.mb_addr = 0x100;
        pciercx_cfg008.s.ml_addr = 0;
        cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG008(pcie_port), pciercx_cfg008.u32);
    }

    /* Prefetchable BAR (PCIERCn_CFG009,PCIERCn_CFG010,PCIERCn_CFG011) */
    /* Most applications should disable the prefetchable BAR by setting */
    /* PCIERCn_CFG011[UMEM_LIMIT],PCIERCn_CFG009[LMEM_LIMIT] < */
    /* PCIERCn_CFG010[UMEM_BASE],PCIERCn_CFG009[LMEM_BASE] */
    {
        cvmx_pciercx_cfg009_t pciercx_cfg009;
        cvmx_pciercx_cfg010_t pciercx_cfg010;
        cvmx_pciercx_cfg011_t pciercx_cfg011;
        pciercx_cfg009.u32 = cvmx_pcie_cfgx_read(pcie_port, CVMX_PCIERCX_CFG009(pcie_port));
        pciercx_cfg010.u32 = cvmx_pcie_cfgx_read(pcie_port, CVMX_PCIERCX_CFG010(pcie_port));
        pciercx_cfg011.u32 = cvmx_pcie_cfgx_read(pcie_port, CVMX_PCIERCX_CFG011(pcie_port));
        pciercx_cfg009.s.lmem_base = 0x100;
        pciercx_cfg009.s.lmem_limit = 0;
        pciercx_cfg010.s.umem_base = 0x100;
        pciercx_cfg011.s.umem_limit = 0;
        cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG009(pcie_port), pciercx_cfg009.u32);
        cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG010(pcie_port), pciercx_cfg010.u32);
        cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG011(pcie_port), pciercx_cfg011.u32);
    }

    /* System Error Interrupt Enables (PCIERCn_CFG035[SECEE,SEFEE,SENFEE]) */
    /* PME Interrupt Enables (PCIERCn_CFG035[PMEIE]) */
    {
        cvmx_pciercx_cfg035_t pciercx_cfg035;
        pciercx_cfg035.u32 = cvmx_pcie_cfgx_read(pcie_port, CVMX_PCIERCX_CFG035(pcie_port));
        pciercx_cfg035.s.secee = 1; /* System error on correctable error enable. */
        pciercx_cfg035.s.sefee = 1; /* System error on fatal error enable. */
        pciercx_cfg035.s.senfee = 1; /* System error on non-fatal error enable. */
        pciercx_cfg035.s.pmeie = 1; /* PME interrupt enable. */
        cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG035(pcie_port), pciercx_cfg035.u32);
    }

    /* Advanced Error Recovery Interrupt Enables */
    /* (PCIERCn_CFG075[CERE,NFERE,FERE]) */
    {
        cvmx_pciercx_cfg075_t pciercx_cfg075;
        pciercx_cfg075.u32 = cvmx_pcie_cfgx_read(pcie_port, CVMX_PCIERCX_CFG075(pcie_port));
        pciercx_cfg075.s.cere = 1; /* Correctable error reporting enable. */
        pciercx_cfg075.s.nfere = 1; /* Non-fatal error reporting enable. */
        pciercx_cfg075.s.fere = 1; /* Fatal error reporting enable. */
        cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG075(pcie_port), pciercx_cfg075.u32);
    }

    /* HP Interrupt Enables (PCIERCn_CFG034[HPINT_EN], */
    /* PCIERCn_CFG034[DLLS_EN,CCINT_EN]) */
    {
        cvmx_pciercx_cfg034_t pciercx_cfg034;
        pciercx_cfg034.u32 = cvmx_pcie_cfgx_read(pcie_port, CVMX_PCIERCX_CFG034(pcie_port));
        pciercx_cfg034.s.hpint_en = 1; /* Hot-plug interrupt enable. */
        pciercx_cfg034.s.dlls_en = 1; /* Data Link Layer state changed enable */
        pciercx_cfg034.s.ccint_en = 1; /* Command completed interrupt enable. */
        cvmx_pcie_cfgx_write(pcie_port, CVMX_PCIERCX_CFG034(pcie_port), pciercx_cfg034.u32);
    }
}