#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  core_mask; } ;
typedef  TYPE_1__ cvmx_sysinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_EN2_PPX_IP2 (int) ; 
 int /*<<< orphan*/  CVMX_CIU_INTX_EN0 (int) ; 
 int /*<<< orphan*/  CVMX_CIU_INTX_EN1 (int) ; 
 scalar_t__ CVMX_IRQ_AGL ; 
 scalar_t__ CVMX_IRQ_AGX0 ; 
 scalar_t__ CVMX_IRQ_BOOTDMA ; 
 scalar_t__ CVMX_IRQ_DFA ; 
 scalar_t__ CVMX_IRQ_DFM ; 
 scalar_t__ CVMX_IRQ_DPI ; 
 scalar_t__ CVMX_IRQ_DPI_DMA ; 
 scalar_t__ CVMX_IRQ_FPA ; 
 scalar_t__ CVMX_IRQ_GMX_DRP0 ; 
 scalar_t__ CVMX_IRQ_GPIO0 ; 
 scalar_t__ CVMX_IRQ_IOB ; 
 scalar_t__ CVMX_IRQ_IPD ; 
 scalar_t__ CVMX_IRQ_IPDPPTHR ; 
 scalar_t__ CVMX_IRQ_IPD_DRP ; 
 scalar_t__ CVMX_IRQ_KEY ; 
 scalar_t__ CVMX_IRQ_KEY_ZERO ; 
 scalar_t__ CVMX_IRQ_L2C ; 
 scalar_t__ CVMX_IRQ_LMC0 ; 
 scalar_t__ CVMX_IRQ_MBOX0 ; 
 scalar_t__ CVMX_IRQ_MII0 ; 
 scalar_t__ CVMX_IRQ_MIO ; 
 scalar_t__ CVMX_IRQ_MPI ; 
 scalar_t__ CVMX_IRQ_NAND ; 
 scalar_t__ CVMX_IRQ_PCI_INT0 ; 
 scalar_t__ CVMX_IRQ_PCI_MSI0 ; 
 scalar_t__ CVMX_IRQ_PCM ; 
 scalar_t__ CVMX_IRQ_PEM0 ; 
 scalar_t__ CVMX_IRQ_PEM1 ; 
 scalar_t__ CVMX_IRQ_PIP ; 
 scalar_t__ CVMX_IRQ_PKO ; 
 scalar_t__ CVMX_IRQ_POW ; 
 scalar_t__ CVMX_IRQ_POWIQ ; 
 scalar_t__ CVMX_IRQ_PTP ; 
 scalar_t__ CVMX_IRQ_RAD ; 
 scalar_t__ CVMX_IRQ_RML ; 
 scalar_t__ CVMX_IRQ_RST ; 
 scalar_t__ CVMX_IRQ_SLI ; 
 scalar_t__ CVMX_IRQ_SRIO0 ; 
 scalar_t__ CVMX_IRQ_SRIO1 ; 
 scalar_t__ CVMX_IRQ_SRIO2 ; 
 scalar_t__ CVMX_IRQ_TIM ; 
 scalar_t__ CVMX_IRQ_TIMER0 ; 
 scalar_t__ CVMX_IRQ_TIMER4 ; 
 scalar_t__ CVMX_IRQ_TRACE0 ; 
 scalar_t__ CVMX_IRQ_TWSI0 ; 
 scalar_t__ CVMX_IRQ_UART0 ; 
 scalar_t__ CVMX_IRQ_USB0 ; 
 scalar_t__ CVMX_IRQ_USBCTL ; 
 scalar_t__ CVMX_IRQ_WDOG0 ; 
 scalar_t__ CVMX_IRQ_WORKQ0 ; 
 scalar_t__ CVMX_IRQ_ZIP ; 
 int /*<<< orphan*/  OCTEON_CN61XX ; 
 int /*<<< orphan*/  OCTEON_CN66XX_PASS1_2 ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_interrupt_set_mapping (scalar_t__,int,int) ; 
 int* cvmx_ciu_61xx_timer_to_irq ; 
 int* cvmx_ciu_en0_to_irq ; 
 int* cvmx_ciu_en1_to_irq ; 
 int /*<<< orphan*/  cvmx_coremask_first_core (int /*<<< orphan*/ ) ; 
 int cvmx_get_core_num () ; 
 scalar_t__ cvmx_interrupt_ciu_61xx_timer_mirror ; 
 scalar_t__ cvmx_interrupt_ciu_en0_mirror ; 
 scalar_t__ cvmx_interrupt_ciu_en1_mirror ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ is_core_being_hot_plugged () ; 

__attribute__((used)) static void cvmx_interrupt_ciu_initialize(cvmx_sysinfo_t *sys_info_ptr)
{
    int i;
    int core = cvmx_get_core_num();

    /* Disable all CIU interrupts by default */
    cvmx_interrupt_ciu_en0_mirror = 0;
    cvmx_interrupt_ciu_en1_mirror = 0;
    cvmx_interrupt_ciu_61xx_timer_mirror = 0;
    cvmx_write_csr(CVMX_CIU_INTX_EN0(core * 2), cvmx_interrupt_ciu_en0_mirror);
    cvmx_write_csr(CVMX_CIU_INTX_EN0((core * 2)+1), cvmx_interrupt_ciu_en0_mirror);
    cvmx_write_csr(CVMX_CIU_INTX_EN1(core * 2), cvmx_interrupt_ciu_en1_mirror);
    cvmx_write_csr(CVMX_CIU_INTX_EN1((core * 2)+1), cvmx_interrupt_ciu_en1_mirror);
    if (OCTEON_IS_MODEL(OCTEON_CN61XX) || OCTEON_IS_MODEL(OCTEON_CN66XX_PASS1_2))
        cvmx_write_csr(CVMX_CIU_EN2_PPX_IP2(cvmx_get_core_num()), cvmx_interrupt_ciu_61xx_timer_mirror);

    if (!cvmx_coremask_first_core(sys_info_ptr->core_mask)|| is_core_being_hot_plugged())
        return;

    /* On the first core, set up the maps */
    for (i = 0; i < 64; i++) {
        cvmx_ciu_en0_to_irq[i] = 0xff;
        cvmx_ciu_en1_to_irq[i] = 0xff;
        cvmx_ciu_61xx_timer_to_irq[i] = 0xff;
    }

    /* WORKQ */
    for (i = 0; i < 16; i++)
        __cvmx_interrupt_set_mapping(CVMX_IRQ_WORKQ0 + i, 0, i);
    /* GPIO */
    for (i = 0; i < 16; i++)
        __cvmx_interrupt_set_mapping(CVMX_IRQ_GPIO0 + i, 0, i + 16);

    /* MBOX */
    for (i = 0; i < 2; i++)
        __cvmx_interrupt_set_mapping(CVMX_IRQ_MBOX0 + i, 0, i + 32);

    /* UART */
    __cvmx_interrupt_set_mapping(CVMX_IRQ_UART0 + 0, 0, 34);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_UART0 + 1, 0, 35);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_UART0 + 2, 1, 16);

    /* PCI */
    for (i = 0; i < 4; i++)
        __cvmx_interrupt_set_mapping(CVMX_IRQ_PCI_INT0 + i, 0, i + 36);

    /* MSI */
    for (i = 0; i < 4; i++)
        __cvmx_interrupt_set_mapping(CVMX_IRQ_PCI_MSI0 + i, 0, i + 40);

    /* TWSI */
    __cvmx_interrupt_set_mapping(CVMX_IRQ_TWSI0 + 0, 0, 45);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_TWSI0 + 1, 0, 59);

    /* other */
    __cvmx_interrupt_set_mapping(CVMX_IRQ_RML, 0, 46);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_TRACE0, 0, 47);

    /* GMX_DRP */
    for (i = 0; i < 2; i++)
        __cvmx_interrupt_set_mapping(CVMX_IRQ_GMX_DRP0 + i, 0, i + 48);

    __cvmx_interrupt_set_mapping(CVMX_IRQ_IPD_DRP, 0, 50);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_KEY_ZERO, 0, 51);

    /* TIMER0 */
    for (i = 0; i < 4; i++)
        __cvmx_interrupt_set_mapping(CVMX_IRQ_TIMER0 + i, 0, i + 52);

    /* TIMER4..9 */
    for(i = 0; i < 6; i++)
        __cvmx_interrupt_set_mapping(CVMX_IRQ_TIMER4 + i, 8, i + 4);

    __cvmx_interrupt_set_mapping(CVMX_IRQ_USB0 + 0, 0, 56);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_USB0 + 1, 1, 17);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_PCM, 0, 57);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_MPI, 0, 58);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_POWIQ, 0, 60);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_IPDPPTHR, 0, 61);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_MII0 + 0, 0, 62);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_MII0 + 1, 1, 18);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_BOOTDMA, 0, 63);

    /* WDOG */
    for (i = 0; i < 16; i++)
        __cvmx_interrupt_set_mapping(CVMX_IRQ_WDOG0 + i, 1, i);

    __cvmx_interrupt_set_mapping(CVMX_IRQ_NAND, 1, 19);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_MIO, 1, 20);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_IOB, 1, 21);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_FPA, 1, 22);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_POW, 1, 23);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_L2C, 1, 24);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_IPD, 1, 25);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_PIP, 1, 26);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_PKO, 1, 27);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_ZIP, 1, 28);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_TIM, 1, 29);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_RAD, 1, 30);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_KEY, 1, 31);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_DFA, 1, 32);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_USBCTL, 1, 33);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_SLI, 1, 34);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_DPI, 1, 35);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_AGX0, 1, 36);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_AGX0 + 1, 1, 37);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_DPI_DMA, 1, 40);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_AGL, 1, 46);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_PTP, 1, 47);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_PEM0, 1, 48);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_PEM1, 1, 49);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_SRIO0, 1, 50);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_SRIO1, 1, 51);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_LMC0, 1, 52);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_DFM, 1, 56);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_SRIO2, 1, 60);
    __cvmx_interrupt_set_mapping(CVMX_IRQ_RST, 1, 63);
}