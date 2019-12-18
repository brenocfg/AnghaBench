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
typedef  int* vuip ;

/* Variables and functions */
 int /*<<< orphan*/  MCPCIA_HOSE2MID (int) ; 
 scalar_t__ MCPCIA_INT_MASK0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static inline void
rawhide_update_irq_hw(int hose, int mask)
{
	*(vuip)MCPCIA_INT_MASK0(MCPCIA_HOSE2MID(hose)) = mask;
	mb();
	*(vuip)MCPCIA_INT_MASK0(MCPCIA_HOSE2MID(hose));
}