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
struct ath_hal_5212 {int /*<<< orphan*/  ah_txTrigLev; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 struct ath_hal_5212* AH5212 (struct ath_hal*) ; 
 int AR_9285_PCU_TXBUF_CTRL_USABLE_SIZE ; 
 int /*<<< orphan*/  AR_AHB_MODE ; 
 int /*<<< orphan*/  AR_AHB_PREFETCH_RD_EN ; 
 int AR_FTRIG ; 
 int /*<<< orphan*/  AR_PCU_TXBUF_CTRL ; 
 int AR_PCU_TXBUF_CTRL_USABLE_SIZE ; 
 int /*<<< orphan*/  AR_RXCFG ; 
 int AR_RXCFG_DMASZ_128B ; 
 int AR_RXCFG_DMASZ_MASK ; 
 int /*<<< orphan*/  AR_RXFIFO_CFG ; 
 scalar_t__ AR_SREV_KITE (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_TXCFG ; 
 int AR_TXCFG_DMASZ_128B ; 
 int AR_TXCFG_DMASZ_MASK ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int SM (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ar5416InitDMA(struct ath_hal *ah)
{
	struct ath_hal_5212 *ahp = AH5212(ah);

	/*
	 * set AHB_MODE not to do cacheline prefetches
	 */
	OS_REG_SET_BIT(ah, AR_AHB_MODE, AR_AHB_PREFETCH_RD_EN);

	/*
	 * let mac dma reads be in 128 byte chunks
	 */
	OS_REG_WRITE(ah, AR_TXCFG, 
		(OS_REG_READ(ah, AR_TXCFG) & ~AR_TXCFG_DMASZ_MASK) | AR_TXCFG_DMASZ_128B);

	/*
	 * let mac dma writes be in 128 byte chunks
	 */
	/*
	 * XXX If you change this, you must change the headroom
	 * assigned in ah_maxTxTrigLev - see ar5416InitState().
	 */
	OS_REG_WRITE(ah, AR_RXCFG, 
		(OS_REG_READ(ah, AR_RXCFG) & ~AR_RXCFG_DMASZ_MASK) | AR_RXCFG_DMASZ_128B);

	/* restore TX trigger level */
	OS_REG_WRITE(ah, AR_TXCFG,
		(OS_REG_READ(ah, AR_TXCFG) &~ AR_FTRIG) |
		    SM(ahp->ah_txTrigLev, AR_FTRIG));

	/*
	 * Setup receive FIFO threshold to hold off TX activities
	 */
	OS_REG_WRITE(ah, AR_RXFIFO_CFG, 0x200);
	
	/*
	 * reduce the number of usable entries in PCU TXBUF to avoid
	 * wrap around.
	 */
	if (AR_SREV_KITE(ah))
		/*
		 * For AR9285 the number of Fifos are reduced to half.
		 * So set the usable tx buf size also to half to
		 * avoid data/delimiter underruns
		 */
		OS_REG_WRITE(ah, AR_PCU_TXBUF_CTRL, AR_9285_PCU_TXBUF_CTRL_USABLE_SIZE);
	else
		OS_REG_WRITE(ah, AR_PCU_TXBUF_CTRL, AR_PCU_TXBUF_CTRL_USABLE_SIZE);
}