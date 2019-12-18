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
struct atiixp_info {scalar_t__ codec_not_ready_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATI_REG_CMD ; 
 int ATI_REG_CMD_IN_DMA_EN ; 
 int ATI_REG_CMD_OUT_DMA_EN ; 
 int ATI_REG_CMD_SPDF_OUT_EN ; 
 int /*<<< orphan*/  ATI_REG_IER ; 
 int CODEC_CHECK_BITS ; 
 int /*<<< orphan*/  atiixp_disable_interrupts (struct atiixp_info*) ; 
 int /*<<< orphan*/  atiixp_lock (struct atiixp_info*) ; 
 int atiixp_rd (struct atiixp_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atiixp_reset_aclink (struct atiixp_info*) ; 
 int /*<<< orphan*/  atiixp_unlock (struct atiixp_info*) ; 
 int /*<<< orphan*/  atiixp_wr (struct atiixp_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
atiixp_chip_pre_init(struct atiixp_info *sc)
{
	uint32_t value;

	atiixp_lock(sc);

	/* disable interrupts */
	atiixp_disable_interrupts(sc);

	/* clear all DMA enables (preserving rest of settings) */
	value = atiixp_rd(sc, ATI_REG_CMD);
	value &= ~(ATI_REG_CMD_IN_DMA_EN | ATI_REG_CMD_OUT_DMA_EN |
	    ATI_REG_CMD_SPDF_OUT_EN );
	atiixp_wr(sc, ATI_REG_CMD, value);

	/* reset aclink */
	atiixp_reset_aclink(sc);

	sc->codec_not_ready_bits = 0;

	/* enable all codecs to interrupt as well as the new frame interrupt */
	atiixp_wr(sc, ATI_REG_IER, CODEC_CHECK_BITS);

	atiixp_unlock(sc);
}