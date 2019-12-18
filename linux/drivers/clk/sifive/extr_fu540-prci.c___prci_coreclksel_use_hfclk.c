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
typedef  int /*<<< orphan*/  u32 ;
struct __prci_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRCI_CORECLKSEL_CORECLKSEL_MASK ; 
 int /*<<< orphan*/  PRCI_CORECLKSEL_OFFSET ; 
 int /*<<< orphan*/  __prci_readl (struct __prci_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __prci_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct __prci_data*) ; 

__attribute__((used)) static void __prci_coreclksel_use_hfclk(struct __prci_data *pd)
{
	u32 r;

	r = __prci_readl(pd, PRCI_CORECLKSEL_OFFSET);
	r |= PRCI_CORECLKSEL_CORECLKSEL_MASK;
	__prci_writel(r, PRCI_CORECLKSEL_OFFSET, pd);

	r = __prci_readl(pd, PRCI_CORECLKSEL_OFFSET); /* barrier */
}