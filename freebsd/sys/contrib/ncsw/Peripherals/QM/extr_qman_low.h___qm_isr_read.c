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
typedef  int /*<<< orphan*/  uint32_t ;
struct qm_portal {int /*<<< orphan*/  addr; } ;
typedef  enum qm_isr_reg { ____Placeholder_qm_isr_reg } qm_isr_reg ;

/* Variables and functions */
 scalar_t__ REG_ISR ; 
 int /*<<< orphan*/  __qm_in (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static __inline__ uint32_t __qm_isr_read(struct qm_portal *portal, enum qm_isr_reg n)
{
    return __qm_in(&portal->addr, REG_ISR + (n << 2));
}