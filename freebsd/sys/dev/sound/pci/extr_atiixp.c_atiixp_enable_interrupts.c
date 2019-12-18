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
struct atiixp_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATI_REG_IER ; 
 int ATI_REG_IER_IN_XRUN_EN ; 
 int ATI_REG_IER_IO_STATUS_EN ; 
 int ATI_REG_IER_OUT_XRUN_EN ; 
 int ATI_REG_IER_SPDF_STATUS_EN ; 
 int ATI_REG_IER_SPDF_XRUN_EN ; 
 int /*<<< orphan*/  ATI_REG_ISR ; 
 int atiixp_rd (struct atiixp_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atiixp_wr (struct atiixp_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
atiixp_enable_interrupts(struct atiixp_info *sc)
{
	uint32_t value;

	/* clear all pending */
	atiixp_wr(sc, ATI_REG_ISR, 0xffffffff);

	/* enable all relevant interrupt sources we can handle */
	value = atiixp_rd(sc, ATI_REG_IER);

	value |= ATI_REG_IER_IO_STATUS_EN;

	/*
	 * Disable / ignore internal xrun/spdf interrupt flags
	 * since it doesn't interest us (for now).
	 */
#if 1
	value &= ~(ATI_REG_IER_IN_XRUN_EN | ATI_REG_IER_OUT_XRUN_EN |
	    ATI_REG_IER_SPDF_XRUN_EN | ATI_REG_IER_SPDF_STATUS_EN);
#else
	value |= ATI_REG_IER_IN_XRUN_EN;
	value |= ATI_REG_IER_OUT_XRUN_EN;

	value |= ATI_REG_IER_SPDF_XRUN_EN;
	value |= ATI_REG_IER_SPDF_STATUS_EN;
#endif

	atiixp_wr(sc, ATI_REG_IER, value);
}