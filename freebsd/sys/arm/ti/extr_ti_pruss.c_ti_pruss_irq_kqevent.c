#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ti_pruss_irqsc {long last; } ;
struct knote {long kn_data; struct ti_pruss_irqsc* kn_hook; } ;

/* Variables and functions */

__attribute__((used)) static int
ti_pruss_irq_kqevent(struct knote *kn, long hint)
{
    struct ti_pruss_irqsc* irq_sc;
    int notify;

    irq_sc = kn->kn_hook;

    if (hint > 0)
        kn->kn_data = hint - 2;

    if (hint > 0 || irq_sc->last > 0)
        notify = 1;
    else
        notify = 0;

    irq_sc->last = hint;

    return (notify);
}