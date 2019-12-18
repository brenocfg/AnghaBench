#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {TYPE_1__* handlers; } ;
struct TYPE_3__ {int handler_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_OR_MASK (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ CVMX_CIU2_EN_PPX_IP2_MBOX_W1C (int) ; 
 scalar_t__ CVMX_CIU2_EN_PPX_IP2_MBOX_W1S (int) ; 
 scalar_t__ CVMX_CIU2_EN_PPX_IP2_WRKQ_W1C (int) ; 
 scalar_t__ CVMX_CIU2_EN_PPX_IP2_WRKQ_W1S (int) ; 
 int CVMX_IRQ_MAX ; 
 int CVMX_IRQ_MIPS7 ; 
 int cvmx_get_core_num () ; 
 int /*<<< orphan*/  cvmx_interrupt_disable_save () ; 
 int /*<<< orphan*/  cvmx_interrupt_restore (int /*<<< orphan*/ ) ; 
 TYPE_2__ cvmx_interrupt_state ; 
 int /*<<< orphan*/  cvmx_write_csr (scalar_t__,unsigned long long) ; 

__attribute__((used)) static void __cvmx_interrupt_ciu2_mask_unmask_irq(int irq_number, int op)
{

    if (irq_number < 0 || irq_number >= CVMX_IRQ_MAX)
        return;

    if (irq_number <=  CVMX_IRQ_MIPS7) {
        uint32_t flags, mask;

        flags = cvmx_interrupt_disable_save();
        asm volatile ("mfc0 %0,$12,0" : "=r" (mask));
        CLEAR_OR_MASK(mask, 1 << (8 + irq_number), op);
        asm volatile ("mtc0 %0,$12,0" : : "r" (mask));
        cvmx_interrupt_restore(flags);
    } else {
        int idx;
        uint64_t reg;
        int core = cvmx_get_core_num();

        int bit = cvmx_interrupt_state.handlers[irq_number].handler_data;

        if (bit < 0)
            return;

        idx = bit >> 6;
        bit &= 0x3f;
        if (idx > 7) {
            /* MBOX */
            if (op)
                reg = CVMX_CIU2_EN_PPX_IP2_MBOX_W1C(core);
            else
                reg = CVMX_CIU2_EN_PPX_IP2_MBOX_W1S(core);
        } else {
            if (op)
                reg = CVMX_CIU2_EN_PPX_IP2_WRKQ_W1C(core) + (0x1000 * idx);
            else
                reg = CVMX_CIU2_EN_PPX_IP2_WRKQ_W1S(core) + (0x1000 * idx);
        }
        cvmx_write_csr(reg, 1ull << bit);
    }
}