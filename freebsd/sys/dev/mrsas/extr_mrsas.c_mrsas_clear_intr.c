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
typedef  int u_int32_t ;
struct mrsas_softc {int dummy; } ;

/* Variables and functions */
 int MFI_FUSION_ENABLE_INTERRUPT_MASK ; 
 int mrsas_read_reg_with_retries (struct mrsas_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrsas_reg_set ; 
 int /*<<< orphan*/  offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outbound_intr_status ; 

__attribute__((used)) static int
mrsas_clear_intr(struct mrsas_softc *sc)
{
	u_int32_t status;

	/* Read received interrupt */
	status = mrsas_read_reg_with_retries(sc, offsetof(mrsas_reg_set, outbound_intr_status));

	/* Not our interrupt, so just return */
	if (!(status & MFI_FUSION_ENABLE_INTERRUPT_MASK))
		return (0);

	/* We got a reply interrupt */
	return (1);
}