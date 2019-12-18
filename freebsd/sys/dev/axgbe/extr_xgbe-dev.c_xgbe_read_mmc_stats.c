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
struct xgbe_mmc_stats {int /*<<< orphan*/  rxwatchdogerror; int /*<<< orphan*/  rxvlanframes_gb; int /*<<< orphan*/  rxfifooverflow; int /*<<< orphan*/  rxpauseframes; int /*<<< orphan*/  rxoutofrangetype; int /*<<< orphan*/  rxlengtherror; int /*<<< orphan*/  rxunicastframes_g; int /*<<< orphan*/  rx1024tomaxoctets_gb; int /*<<< orphan*/  rx512to1023octets_gb; int /*<<< orphan*/  rx256to511octets_gb; int /*<<< orphan*/  rx128to255octets_gb; int /*<<< orphan*/  rx65to127octets_gb; int /*<<< orphan*/  rx64octets_gb; int /*<<< orphan*/  rxoversize_g; int /*<<< orphan*/  rxundersize_g; int /*<<< orphan*/  rxjabbererror; int /*<<< orphan*/  rxrunterror; int /*<<< orphan*/  rxcrcerror; int /*<<< orphan*/  rxmulticastframes_g; int /*<<< orphan*/  rxbroadcastframes_g; int /*<<< orphan*/  rxoctetcount_g; int /*<<< orphan*/  rxoctetcount_gb; int /*<<< orphan*/  rxframecount_gb; int /*<<< orphan*/  txvlanframes_g; int /*<<< orphan*/  txpauseframes; int /*<<< orphan*/  txframecount_g; int /*<<< orphan*/  txoctetcount_g; int /*<<< orphan*/  txunderflowerror; int /*<<< orphan*/  txbroadcastframes_g; int /*<<< orphan*/  txmulticastframes_gb; int /*<<< orphan*/  txunicastframes_gb; int /*<<< orphan*/  tx1024tomaxoctets_gb; int /*<<< orphan*/  tx512to1023octets_gb; int /*<<< orphan*/  tx256to511octets_gb; int /*<<< orphan*/  tx128to255octets_gb; int /*<<< orphan*/  tx65to127octets_gb; int /*<<< orphan*/  tx64octets_gb; int /*<<< orphan*/  txmulticastframes_g; int /*<<< orphan*/  txframecount_gb; int /*<<< orphan*/  txoctetcount_gb; } ;
struct xgbe_prv_data {struct xgbe_mmc_stats mmc_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCF ; 
 int /*<<< orphan*/  MMC_CR ; 
 int /*<<< orphan*/  MMC_RX1024TOMAXOCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_RX128TO255OCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_RX256TO511OCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_RX512TO1023OCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_RX64OCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_RX65TO127OCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_RXBROADCASTFRAMES_G_LO ; 
 int /*<<< orphan*/  MMC_RXCRCERROR_LO ; 
 int /*<<< orphan*/  MMC_RXFIFOOVERFLOW_LO ; 
 int /*<<< orphan*/  MMC_RXFRAMECOUNT_GB_LO ; 
 int /*<<< orphan*/  MMC_RXJABBERERROR ; 
 int /*<<< orphan*/  MMC_RXLENGTHERROR_LO ; 
 int /*<<< orphan*/  MMC_RXMULTICASTFRAMES_G_LO ; 
 int /*<<< orphan*/  MMC_RXOCTETCOUNT_GB_LO ; 
 int /*<<< orphan*/  MMC_RXOCTETCOUNT_G_LO ; 
 int /*<<< orphan*/  MMC_RXOUTOFRANGETYPE_LO ; 
 int /*<<< orphan*/  MMC_RXOVERSIZE_G ; 
 int /*<<< orphan*/  MMC_RXPAUSEFRAMES_LO ; 
 int /*<<< orphan*/  MMC_RXRUNTERROR ; 
 int /*<<< orphan*/  MMC_RXUNDERSIZE_G ; 
 int /*<<< orphan*/  MMC_RXUNICASTFRAMES_G_LO ; 
 int /*<<< orphan*/  MMC_RXVLANFRAMES_GB_LO ; 
 int /*<<< orphan*/  MMC_RXWATCHDOGERROR ; 
 int /*<<< orphan*/  MMC_TX1024TOMAXOCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_TX128TO255OCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_TX256TO511OCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_TX512TO1023OCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_TX64OCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_TX65TO127OCTETS_GB_LO ; 
 int /*<<< orphan*/  MMC_TXBROADCASTFRAMES_GB_LO ; 
 int /*<<< orphan*/  MMC_TXBROADCASTFRAMES_G_LO ; 
 int /*<<< orphan*/  MMC_TXFRAMECOUNT_GB_LO ; 
 int /*<<< orphan*/  MMC_TXFRAMECOUNT_G_LO ; 
 int /*<<< orphan*/  MMC_TXMULTICASTFRAMES_GB_LO ; 
 int /*<<< orphan*/  MMC_TXMULTICASTFRAMES_G_LO ; 
 int /*<<< orphan*/  MMC_TXOCTETCOUNT_GB_LO ; 
 int /*<<< orphan*/  MMC_TXOCTETCOUNT_G_LO ; 
 int /*<<< orphan*/  MMC_TXPAUSEFRAMES_LO ; 
 int /*<<< orphan*/  MMC_TXUNDERFLOWERROR_LO ; 
 int /*<<< orphan*/  MMC_TXUNICASTFRAMES_GB_LO ; 
 int /*<<< orphan*/  MMC_TXVLANFRAMES_G_LO ; 
 int /*<<< orphan*/  XGMAC_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xgbe_mmc_read (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_read_mmc_stats(struct xgbe_prv_data *pdata)
{
	struct xgbe_mmc_stats *stats = &pdata->mmc_stats;

	/* Freeze counters */
	XGMAC_IOWRITE_BITS(pdata, MMC_CR, MCF, 1);

	stats->txoctetcount_gb +=
		xgbe_mmc_read(pdata, MMC_TXOCTETCOUNT_GB_LO);

	stats->txframecount_gb +=
		xgbe_mmc_read(pdata, MMC_TXFRAMECOUNT_GB_LO);

	stats->txbroadcastframes_g +=
		xgbe_mmc_read(pdata, MMC_TXBROADCASTFRAMES_G_LO);

	stats->txmulticastframes_g +=
		xgbe_mmc_read(pdata, MMC_TXMULTICASTFRAMES_G_LO);

	stats->tx64octets_gb +=
		xgbe_mmc_read(pdata, MMC_TX64OCTETS_GB_LO);

	stats->tx65to127octets_gb +=
		xgbe_mmc_read(pdata, MMC_TX65TO127OCTETS_GB_LO);

	stats->tx128to255octets_gb +=
		xgbe_mmc_read(pdata, MMC_TX128TO255OCTETS_GB_LO);

	stats->tx256to511octets_gb +=
		xgbe_mmc_read(pdata, MMC_TX256TO511OCTETS_GB_LO);

	stats->tx512to1023octets_gb +=
		xgbe_mmc_read(pdata, MMC_TX512TO1023OCTETS_GB_LO);

	stats->tx1024tomaxoctets_gb +=
		xgbe_mmc_read(pdata, MMC_TX1024TOMAXOCTETS_GB_LO);

	stats->txunicastframes_gb +=
		xgbe_mmc_read(pdata, MMC_TXUNICASTFRAMES_GB_LO);

	stats->txmulticastframes_gb +=
		xgbe_mmc_read(pdata, MMC_TXMULTICASTFRAMES_GB_LO);

	stats->txbroadcastframes_g +=
		xgbe_mmc_read(pdata, MMC_TXBROADCASTFRAMES_GB_LO);

	stats->txunderflowerror +=
		xgbe_mmc_read(pdata, MMC_TXUNDERFLOWERROR_LO);

	stats->txoctetcount_g +=
		xgbe_mmc_read(pdata, MMC_TXOCTETCOUNT_G_LO);

	stats->txframecount_g +=
		xgbe_mmc_read(pdata, MMC_TXFRAMECOUNT_G_LO);

	stats->txpauseframes +=
		xgbe_mmc_read(pdata, MMC_TXPAUSEFRAMES_LO);

	stats->txvlanframes_g +=
		xgbe_mmc_read(pdata, MMC_TXVLANFRAMES_G_LO);

	stats->rxframecount_gb +=
		xgbe_mmc_read(pdata, MMC_RXFRAMECOUNT_GB_LO);

	stats->rxoctetcount_gb +=
		xgbe_mmc_read(pdata, MMC_RXOCTETCOUNT_GB_LO);

	stats->rxoctetcount_g +=
		xgbe_mmc_read(pdata, MMC_RXOCTETCOUNT_G_LO);

	stats->rxbroadcastframes_g +=
		xgbe_mmc_read(pdata, MMC_RXBROADCASTFRAMES_G_LO);

	stats->rxmulticastframes_g +=
		xgbe_mmc_read(pdata, MMC_RXMULTICASTFRAMES_G_LO);

	stats->rxcrcerror +=
		xgbe_mmc_read(pdata, MMC_RXCRCERROR_LO);

	stats->rxrunterror +=
		xgbe_mmc_read(pdata, MMC_RXRUNTERROR);

	stats->rxjabbererror +=
		xgbe_mmc_read(pdata, MMC_RXJABBERERROR);

	stats->rxundersize_g +=
		xgbe_mmc_read(pdata, MMC_RXUNDERSIZE_G);

	stats->rxoversize_g +=
		xgbe_mmc_read(pdata, MMC_RXOVERSIZE_G);

	stats->rx64octets_gb +=
		xgbe_mmc_read(pdata, MMC_RX64OCTETS_GB_LO);

	stats->rx65to127octets_gb +=
		xgbe_mmc_read(pdata, MMC_RX65TO127OCTETS_GB_LO);

	stats->rx128to255octets_gb +=
		xgbe_mmc_read(pdata, MMC_RX128TO255OCTETS_GB_LO);

	stats->rx256to511octets_gb +=
		xgbe_mmc_read(pdata, MMC_RX256TO511OCTETS_GB_LO);

	stats->rx512to1023octets_gb +=
		xgbe_mmc_read(pdata, MMC_RX512TO1023OCTETS_GB_LO);

	stats->rx1024tomaxoctets_gb +=
		xgbe_mmc_read(pdata, MMC_RX1024TOMAXOCTETS_GB_LO);

	stats->rxunicastframes_g +=
		xgbe_mmc_read(pdata, MMC_RXUNICASTFRAMES_G_LO);

	stats->rxlengtherror +=
		xgbe_mmc_read(pdata, MMC_RXLENGTHERROR_LO);

	stats->rxoutofrangetype +=
		xgbe_mmc_read(pdata, MMC_RXOUTOFRANGETYPE_LO);

	stats->rxpauseframes +=
		xgbe_mmc_read(pdata, MMC_RXPAUSEFRAMES_LO);

	stats->rxfifooverflow +=
		xgbe_mmc_read(pdata, MMC_RXFIFOOVERFLOW_LO);

	stats->rxvlanframes_gb +=
		xgbe_mmc_read(pdata, MMC_RXVLANFRAMES_GB_LO);

	stats->rxwatchdogerror +=
		xgbe_mmc_read(pdata, MMC_RXWATCHDOGERROR);

	/* Un-freeze counters */
	XGMAC_IOWRITE_BITS(pdata, MMC_CR, MCF, 0);
}