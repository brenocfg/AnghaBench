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
typedef  int uint32_t ;
struct __cvmx_interrupt_handler {int /*<<< orphan*/  data; int /*<<< orphan*/  (* handler ) (int,int*,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {struct __cvmx_interrupt_handler* handlers; int /*<<< orphan*/  (* exception_handler ) (int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_MF_CACHE_ERR (int) ; 
 int /*<<< orphan*/  CVMX_MT_CACHE_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_MT_DCACHE_ERR (int) ; 
 int /*<<< orphan*/  OCTEON_CN3XXX ; 
 int /*<<< orphan*/  OCTEON_CN5XXX ; 
 int /*<<< orphan*/  OCTEON_CN6XXX ; 
 int /*<<< orphan*/  OCTEON_CNF7XXX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_interrupt_default_exception_handler (int*) ; 
 int cvmx_get_core_num () ; 
 TYPE_1__ cvmx_interrupt_state ; 
 int /*<<< orphan*/  cvmx_safe_printf (char*,int,...) ; 
 int /*<<< orphan*/  stub1 (int*) ; 
 int /*<<< orphan*/  stub2 (int,int*,int /*<<< orphan*/ ) ; 

void cvmx_interrupt_do_irq(uint64_t *registers)
{
    uint64_t        mask;
    uint64_t        cause;
    uint64_t        status;
    uint64_t        cache_err;
    int             i;
    uint32_t exc_vec;
    /* Determine the cause of the interrupt */
    asm volatile ("dmfc0 %0,$13,0" : "=r" (cause));
    asm volatile ("dmfc0 %0,$12,0" : "=r" (status));
    /* In case of exception, clear all interrupts to avoid recursive interrupts.
       Also clear EXL bit to display the correct PC value. */
    if ((cause & 0x7c) == 0)
    {
        asm volatile ("dmtc0 %0, $12, 0" : : "r" (status & ~(0xff02)));
    }
    /* The assembly stub at each exception vector saves its address in k1 when
    ** it calls the stage 2 handler.  We use this to compute the exception vector
    ** that brought us here */
    exc_vec = (uint32_t)(registers[27] & 0x780);  /* Mask off bits we need to ignore */

    /* Check for cache errors.  The cache errors go to a separate exception vector,
    ** so we will only check these if we got here from a cache error exception, and
    ** the ERL (error level) bit is set. */
    i = cvmx_get_core_num();
    if (exc_vec == 0x100 && (status & 0x4))
    {
        CVMX_MF_CACHE_ERR(cache_err);

        /* Use copy of DCACHE_ERR register that early exception stub read */
        if (OCTEON_IS_MODEL(OCTEON_CN3XXX) || OCTEON_IS_MODEL(OCTEON_CN5XXX))
        {
            if (registers[34] & 0x1)
                cvmx_safe_printf("Dcache error detected: core: %d, way: %d, va 7:3: 0x%x\n", i, (int)(registers[34] >> 8) & 0x3f, (int)(registers[34] >> 3) & 0x1f);
            else if (cache_err & 0x1)
                cvmx_safe_printf("Icache error detected: core: %d, set: %d, way : %d, va 6:3 = 0x%x\n", i, (int)(cache_err >> 5) & 0x3f, (int)(cache_err >> 3) & 0x3, (int)(cache_err >> 11) & 0xf);
            else
                cvmx_safe_printf("Cache error exception: core %d\n", i);
        }
        else
        {
            if (registers[34] & 0x1)
                cvmx_safe_printf("Dcache error detected: core: %d, way: %d, va 9:7: 0x%x\n", i, (int)(registers[34] >> 10) & 0x1f, (int)(registers[34] >> 7) & 0x3);
            else if (cache_err & 0x1)
                cvmx_safe_printf("Icache error detected: core: %d, way : %d, va 9:3 = 0x%x\n", i, (int)(cache_err >> 10) & 0x3f, (int)(cache_err >> 3) & 0x7f);
            else
                cvmx_safe_printf("Cache error exception: core %d\n", i);
        }
        CVMX_MT_DCACHE_ERR(1);
        CVMX_MT_CACHE_ERR(0);
    }

    /* The bus error exceptions can occur due to DID timeout or write buffer,
       check by reading COP0_CACHEERRD */
    if (OCTEON_IS_MODEL(OCTEON_CN6XXX) || OCTEON_IS_MODEL(OCTEON_CNF7XXX))
    {
        i = cvmx_get_core_num();
        if (registers[34] & 0x4)
        {
            cvmx_safe_printf("Bus error detected due to DID timeout: core: %d\n", i);
            CVMX_MT_DCACHE_ERR(4);
        }
        else if (registers[34] & 0x2)
        {
            cvmx_safe_printf("Bus error detected due to write buffer parity: core: %d\n", i);
            CVMX_MT_DCACHE_ERR(2);
        }
    }

    if ((cause & 0x7c) != 0)
    {
        cvmx_interrupt_state.exception_handler(registers);
        goto return_from_interrupt;
    }

    /* Convert the cause into an active mask */
    mask = ((cause & status) >> 8) & 0xff;
    if (mask == 0)
    {
        goto return_from_interrupt; /* Spurious interrupt */
    }

    for (i=0; i<8; i++)
    {
        if (mask & (1<<i))
        {
            struct __cvmx_interrupt_handler *h = cvmx_interrupt_state.handlers + i;
            h->handler(i, registers, h->data);
            goto return_from_interrupt;
        }
    }

    /* We should never get here */
    __cvmx_interrupt_default_exception_handler(registers);

return_from_interrupt:
    /* Restore Status register before returning from exception. */
    asm volatile ("dmtc0 %0, $12, 0" : : "r" (status));
}