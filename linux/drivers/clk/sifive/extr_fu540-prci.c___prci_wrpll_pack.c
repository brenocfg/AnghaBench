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
typedef  int u32 ;
struct wrpll_cfg {int divr; int divf; int divq; int range; } ;

/* Variables and functions */
 int PRCI_COREPLLCFG0_DIVF_SHIFT ; 
 int PRCI_COREPLLCFG0_DIVQ_SHIFT ; 
 int PRCI_COREPLLCFG0_DIVR_SHIFT ; 
 int PRCI_COREPLLCFG0_FSE_MASK ; 
 int PRCI_COREPLLCFG0_RANGE_SHIFT ; 

__attribute__((used)) static u32 __prci_wrpll_pack(const struct wrpll_cfg *c)
{
	u32 r = 0;

	r |= c->divr << PRCI_COREPLLCFG0_DIVR_SHIFT;
	r |= c->divf << PRCI_COREPLLCFG0_DIVF_SHIFT;
	r |= c->divq << PRCI_COREPLLCFG0_DIVQ_SHIFT;
	r |= c->range << PRCI_COREPLLCFG0_RANGE_SHIFT;

	/* external feedback mode not supported */
	r |= PRCI_COREPLLCFG0_FSE_MASK;

	return r;
}