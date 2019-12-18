#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct __cvmx_interrupt_handler {int /*<<< orphan*/  data; int /*<<< orphan*/  (* handler ) (int,int*,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {struct __cvmx_interrupt_handler* handlers; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_EN2_PPX_IP2 (int) ; 
 int /*<<< orphan*/  CVMX_CIU_INTX_EN0 (int) ; 
 int /*<<< orphan*/  CVMX_CIU_INTX_EN1 (int) ; 
 int /*<<< orphan*/  CVMX_CIU_INTX_SUM0 (int) ; 
 int /*<<< orphan*/  CVMX_CIU_INT_SUM1 ; 
 int /*<<< orphan*/  CVMX_CIU_SUM2_PPX_IP2 (int) ; 
 int /*<<< orphan*/  CVMX_DCLZ (int,int) ; 
 int CVMX_IRQ_MIPS2 ; 
 int /*<<< orphan*/  OCTEON_CN61XX ; 
 int /*<<< orphan*/  OCTEON_CN66XX_PASS1_2 ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int* cvmx_ciu_61xx_timer_to_irq ; 
 int* cvmx_ciu_en0_to_irq ; 
 int* cvmx_ciu_en1_to_irq ; 
 int cvmx_get_core_num () ; 
 unsigned long long cvmx_interrupt_ciu_61xx_timer_mirror ; 
 unsigned long long cvmx_interrupt_ciu_en0_mirror ; 
 unsigned long long cvmx_interrupt_ciu_en1_mirror ; 
 TYPE_1__ cvmx_interrupt_state ; 
 unsigned long long cvmx_read_csr (int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_unlikely (int) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  stub1 (int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __cvmx_interrupt_ciu(int irq_number, uint64_t *registers, void *user_arg)
{
    int ciu_offset;
    uint64_t irq_mask;
    uint64_t irq;
    int bit;
    int core = cvmx_get_core_num();

    if (irq_number == CVMX_IRQ_MIPS2) {
        /* Handle EN0 sources */
        ciu_offset = core * 2;
        irq_mask = cvmx_read_csr(CVMX_CIU_INTX_SUM0(ciu_offset)) & cvmx_interrupt_ciu_en0_mirror;
        CVMX_DCLZ(bit, irq_mask);
        bit = 63 - bit;
        /* If ciu_int_sum1<sum2> is set, means its a timer interrupt */
        if (bit == 51 && (OCTEON_IS_MODEL(OCTEON_CN61XX) || OCTEON_IS_MODEL(OCTEON_CN66XX_PASS1_2))) {
            uint64_t irq_mask;
            int bit;
            irq_mask = cvmx_read_csr(CVMX_CIU_SUM2_PPX_IP2(core)) & cvmx_interrupt_ciu_61xx_timer_mirror;
            CVMX_DCLZ(bit, irq_mask);
            bit = 63 - bit;
            /* Handle TIMER(4..9) interrupts */
            if (bit <= 9 && bit >= 4) {
                uint64_t irq = cvmx_ciu_61xx_timer_to_irq[bit];
                if (cvmx_unlikely(irq == 0xff)) {
                    /* No mapping */
                    cvmx_interrupt_ciu_61xx_timer_mirror &= ~(1ull << bit);
                    cvmx_write_csr(CVMX_CIU_EN2_PPX_IP2(core), cvmx_interrupt_ciu_61xx_timer_mirror);
                    return;
                }
                struct __cvmx_interrupt_handler *h = cvmx_interrupt_state.handlers + irq;
                h->handler(irq, registers, h->data);
                return;
            }
        }

        if (bit >= 0) {
            irq = cvmx_ciu_en0_to_irq[bit];
            if (cvmx_unlikely(irq == 0xff)) {
                /* No mapping. */
                cvmx_interrupt_ciu_en0_mirror &= ~(1ull << bit);
                cvmx_write_csr(CVMX_CIU_INTX_EN0(ciu_offset), cvmx_interrupt_ciu_en0_mirror);
                return;
            }
            struct __cvmx_interrupt_handler *h = cvmx_interrupt_state.handlers + irq;
            h->handler(irq, registers, h->data);
            return;
        }
    } else {
        /* Handle EN1 sources */
        ciu_offset = cvmx_get_core_num() * 2 + 1;
        irq_mask = cvmx_read_csr(CVMX_CIU_INT_SUM1) & cvmx_interrupt_ciu_en1_mirror;
        CVMX_DCLZ(bit, irq_mask);
        bit = 63 - bit;
        if (bit >= 0) {
            irq = cvmx_ciu_en1_to_irq[bit];
            if (cvmx_unlikely(irq == 0xff)) {
                /* No mapping. */
                cvmx_interrupt_ciu_en1_mirror &= ~(1ull << bit);
                cvmx_write_csr(CVMX_CIU_INTX_EN1(ciu_offset), cvmx_interrupt_ciu_en1_mirror);
                return;
            }
            struct __cvmx_interrupt_handler *h = cvmx_interrupt_state.handlers + irq;
            h->handler(irq, registers, h->data);
            return;
        }
    }
}