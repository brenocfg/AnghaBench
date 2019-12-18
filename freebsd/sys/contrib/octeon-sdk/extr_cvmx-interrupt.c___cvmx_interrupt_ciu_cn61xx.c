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
 int /*<<< orphan*/  CVMX_CIU_INTX_EN1 (int) ; 
 int /*<<< orphan*/  CVMX_CIU_SUM1_PPX_IP3 (int) ; 
 int /*<<< orphan*/  CVMX_DCLZ (int,int) ; 
 int* cvmx_ciu_en1_to_irq ; 
 int cvmx_get_core_num () ; 
 unsigned long long cvmx_interrupt_ciu_en1_mirror ; 
 TYPE_1__ cvmx_interrupt_state ; 
 unsigned long long cvmx_read_csr (int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_unlikely (int) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  stub1 (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __cvmx_interrupt_ciu_cn61xx(int irq_number, uint64_t *registers, void *user_arg)
{
    /* Handle EN1 sources */
    int core = cvmx_get_core_num();
    int ciu_offset;
    uint64_t irq_mask;
    uint64_t irq;
    int bit;

    ciu_offset = core * 2 + 1;
    irq_mask = cvmx_read_csr(CVMX_CIU_SUM1_PPX_IP3(core)) & cvmx_interrupt_ciu_en1_mirror;
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