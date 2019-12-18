#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_2__ {scalar_t__ halHwUapsdTrig; } ;
struct ath_hal_private {scalar_t__ ah_macRev; scalar_t__ ah_opmode; TYPE_1__ ah_caps; } ;
struct ath_hal_9300 {int rx_buf_size; } ;
struct ath_hal {int dummy; } ;
typedef  TYPE_1__ HAL_CAPABILITIES ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 struct ath_hal_private* AH_PRIVATE (struct ath_hal*) ; 
 scalar_t__ AH_TRUE ; 
 int /*<<< orphan*/  AR_AHB_MODE ; 
 int AR_AHB_PREFETCH_RD_EN ; 
 int /*<<< orphan*/  AR_DATABUF ; 
 int /*<<< orphan*/  AR_FTRIG ; 
 int AR_HPQ_ENABLE ; 
 int AR_HPQ_UAPSD ; 
 int AR_HPQ_UAPSD_TRIGGER_EN ; 
 int /*<<< orphan*/  AR_HP_Q_CONTROL ; 
 int /*<<< orphan*/  AR_PCU_TXBUF_CTRL ; 
 int AR_PCU_TXBUF_CTRL_USABLE_SIZE ; 
 int /*<<< orphan*/  AR_RXBP_THRESH ; 
 int /*<<< orphan*/  AR_RXBP_THRESH_HP ; 
 int /*<<< orphan*/  AR_RXBP_THRESH_LP ; 
 int /*<<< orphan*/  AR_RXCFG ; 
 int AR_RXCFG_DMASZ_128B ; 
 int AR_RXCFG_DMASZ_MASK ; 
 int /*<<< orphan*/  AR_RXFIFO_CFG ; 
 scalar_t__ AR_SREV_REVISION_WASP_12 ; 
 scalar_t__ AR_SREV_WASP (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_TXCFG ; 
 int AR_TXCFG_DMASZ_128B ; 
 int AR_TXCFG_DMASZ_MASK ; 
 scalar_t__ HAL_M_HOSTAP ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar9300_reset_tx_status_ring (struct ath_hal*) ; 

__attribute__((used)) static inline void
ar9300_set_dma(struct ath_hal *ah)
{
    u_int32_t   regval;
    struct ath_hal_9300 *ahp = AH9300(ah);
    struct ath_hal_private *ahpriv = AH_PRIVATE(ah);
    HAL_CAPABILITIES *pCap = &ahpriv->ah_caps;

#if 0
    /*
     * set AHB_MODE not to do cacheline prefetches
     */
    regval = OS_REG_READ(ah, AR_AHB_MODE);
    OS_REG_WRITE(ah, AR_AHB_MODE, regval | AR_AHB_PREFETCH_RD_EN);
#endif

    /*
     * let mac dma reads be in 128 byte chunks
     */
    regval = OS_REG_READ(ah, AR_TXCFG) & ~AR_TXCFG_DMASZ_MASK;
    OS_REG_WRITE(ah, AR_TXCFG, regval | AR_TXCFG_DMASZ_128B);

    /*
     * Restore TX Trigger Level to its pre-reset value.
     * The initial value depends on whether aggregation is enabled, and is
     * adjusted whenever underruns are detected.
     */
    /*
    OS_REG_RMW_FIELD(ah, AR_TXCFG, AR_FTRIG, AH_PRIVATE(ah)->ah_tx_trig_level);
     */
    /* 
     * Osprey 1.0 bug (EV 61936). Don't change trigger level from .ini default.
     * Osprey 2.0 - hardware recommends using the default INI settings.
     */
#if 0
    OS_REG_RMW_FIELD(ah, AR_TXCFG, AR_FTRIG, 0x3f);
#endif
    /*
     * let mac dma writes be in 128 byte chunks
     */
    regval = OS_REG_READ(ah, AR_RXCFG) & ~AR_RXCFG_DMASZ_MASK;
    OS_REG_WRITE(ah, AR_RXCFG, regval | AR_RXCFG_DMASZ_128B);

    /*
     * Setup receive FIFO threshold to hold off TX activities
     */
    OS_REG_WRITE(ah, AR_RXFIFO_CFG, 0x200);

    /*
     * reduce the number of usable entries in PCU TXBUF to avoid
     * wrap around bugs. (bug 20428)
     */
    
    if (AR_SREV_WASP(ah) && 
        (AH_PRIVATE((ah))->ah_macRev > AR_SREV_REVISION_WASP_12)) {
        /* Wasp 1.3 fix for EV#85395 requires usable entries 
         * to be set to 0x500 
         */
        OS_REG_WRITE(ah, AR_PCU_TXBUF_CTRL, 0x500);
    } else {
        OS_REG_WRITE(ah, AR_PCU_TXBUF_CTRL, AR_PCU_TXBUF_CTRL_USABLE_SIZE);
    }

    /*
     * Enable HPQ for UAPSD
     */
    if (pCap->halHwUapsdTrig == AH_TRUE) {
    /* Only enable this if HAL capabilities says it is OK */
        if (AH_PRIVATE(ah)->ah_opmode == HAL_M_HOSTAP) {
            OS_REG_WRITE(ah, AR_HP_Q_CONTROL,
                    AR_HPQ_ENABLE | AR_HPQ_UAPSD | AR_HPQ_UAPSD_TRIGGER_EN);
        }
    } else {
        /* use default value from ini file - which disable HPQ queue usage */
    }

    /*
     * set the transmit status ring
     */
    ar9300_reset_tx_status_ring(ah);

    /*
     * set rxbp threshold.  Must be non-zero for RX_EOL to occur.
     * For Osprey 2.0+, keep the original thresholds
     * otherwise performance is lost due to excessive RX EOL interrupts.
     */
    OS_REG_RMW_FIELD(ah, AR_RXBP_THRESH, AR_RXBP_THRESH_HP, 0x1);
    OS_REG_RMW_FIELD(ah, AR_RXBP_THRESH, AR_RXBP_THRESH_LP, 0x1);

    /*
     * set receive buffer size.
     */
    if (ahp->rx_buf_size) {
        OS_REG_WRITE(ah, AR_DATABUF, ahp->rx_buf_size);
    }
}