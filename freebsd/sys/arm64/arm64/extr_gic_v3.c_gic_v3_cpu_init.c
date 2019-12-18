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
struct gic_v3_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLR ; 
 int /*<<< orphan*/  GIC_PRIORITY_MIN ; 
 int /*<<< orphan*/  ICC_CTLR_EL1_EOIMODE ; 
 int /*<<< orphan*/  ICC_IGRPEN0_EL1_EN ; 
 int /*<<< orphan*/  IGRPEN1 ; 
 int /*<<< orphan*/  gic_icc_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gic_icc_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gic_v3_cpu_enable_sre (struct gic_v3_softc*) ; 
 int /*<<< orphan*/  gic_v3_cpu_priority (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gic_v3_cpu_init(struct gic_v3_softc *sc)
{
	int err;

	/* Enable access to CPU interface via system registers */
	err = gic_v3_cpu_enable_sre(sc);
	if (err != 0)
		return (err);
	/* Priority mask to minimum - accept all interrupts */
	gic_v3_cpu_priority(GIC_PRIORITY_MIN);
	/* Disable EOI mode */
	gic_icc_clear(CTLR, ICC_CTLR_EL1_EOIMODE);
	/* Enable group 1 (insecure) interrups */
	gic_icc_set(IGRPEN1, ICC_IGRPEN0_EL1_EN);

	return (0);
}