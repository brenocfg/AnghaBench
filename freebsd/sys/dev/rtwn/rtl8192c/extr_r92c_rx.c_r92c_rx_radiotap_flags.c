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
typedef  int /*<<< orphan*/  uint8_t ;
struct r92c_rx_stat {int rxdw3; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_RADIOTAP_F_SHORTGI ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_F_SHORTPRE ; 
 int /*<<< orphan*/  MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R92C_RXDW3_RATE ; 
 int /*<<< orphan*/  R92C_RXDW3_SPLCP ; 
 scalar_t__ RTWN_RATE_IS_CCK (int /*<<< orphan*/ ) ; 
 int htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32toh (int) ; 

uint8_t
r92c_rx_radiotap_flags(const void *buf)
{
	const struct r92c_rx_stat *stat = buf;
	uint8_t flags, rate;

	if (!(stat->rxdw3 & htole32(R92C_RXDW3_SPLCP)))
		return (0);

	rate = MS(le32toh(stat->rxdw3), R92C_RXDW3_RATE);
	if (RTWN_RATE_IS_CCK(rate))
		flags = IEEE80211_RADIOTAP_F_SHORTPRE;
	else
		flags = IEEE80211_RADIOTAP_F_SHORTGI;
	return (flags);
}