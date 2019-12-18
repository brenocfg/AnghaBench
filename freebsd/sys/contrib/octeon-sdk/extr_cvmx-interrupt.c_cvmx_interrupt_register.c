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
typedef  int /*<<< orphan*/  cvmx_interrupt_func_t ;
struct TYPE_4__ {TYPE_1__* handlers; } ;
struct TYPE_3__ {void* data; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int CVMX_IRQ_MAX ; 
 int /*<<< orphan*/  CVMX_SYNCWS ; 
 TYPE_2__ cvmx_interrupt_state ; 
 int /*<<< orphan*/  cvmx_warn (char*,int) ; 

void cvmx_interrupt_register(int irq_number, cvmx_interrupt_func_t func, void *user_arg)
{
    if (irq_number >= CVMX_IRQ_MAX || irq_number < 0) {
        cvmx_warn("cvmx_interrupt_register: Illegal irq_number %d\n", irq_number);
        return;
    }
    cvmx_interrupt_state.handlers[irq_number].handler = func;
    cvmx_interrupt_state.handlers[irq_number].data = user_arg;
    CVMX_SYNCWS;
}