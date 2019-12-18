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
typedef  int uint32_t ;
struct memac_regs {int /*<<< orphan*/  ievent; } ;

/* Variables and functions */
 int ioread32be (int /*<<< orphan*/ *) ; 

uint32_t fman_memac_get_event(struct memac_regs *regs, uint32_t ev_mask)
{
    return ioread32be(&regs->ievent) & ev_mask;
}