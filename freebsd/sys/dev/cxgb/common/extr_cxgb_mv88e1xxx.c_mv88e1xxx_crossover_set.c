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
struct cphy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV88E1XXX_SPECIFIC_CNTRL ; 
 int M_PSCR_MDI_XOVER_MODE ; 
 int /*<<< orphan*/  V_PSCR_MDI_XOVER_MODE (int) ; 
 int t3_mdio_change_bits (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88e1xxx_crossover_set(struct cphy *cphy, int crossover)
{
	return t3_mdio_change_bits(cphy, 0, MV88E1XXX_SPECIFIC_CNTRL,
				   V_PSCR_MDI_XOVER_MODE(M_PSCR_MDI_XOVER_MODE),
				   V_PSCR_MDI_XOVER_MODE(crossover));
}