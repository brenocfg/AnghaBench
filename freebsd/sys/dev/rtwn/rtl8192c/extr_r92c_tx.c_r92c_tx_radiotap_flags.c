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
struct r92c_tx_desc {int txdw4; int txdw5; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_RADIOTAP_F_SHORTGI ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_F_SHORTPRE ; 
 int /*<<< orphan*/  R92C_TXDW4_DATA_SHPRE ; 
 int /*<<< orphan*/  R92C_TXDW5_SGI ; 
 int htole32 (int /*<<< orphan*/ ) ; 

uint8_t
r92c_tx_radiotap_flags(const void *buf)
{
	const struct r92c_tx_desc *txd = buf;
	uint8_t flags;

	flags = 0;
	if (txd->txdw4 & htole32(R92C_TXDW4_DATA_SHPRE))
		flags |= IEEE80211_RADIOTAP_F_SHORTPRE;
	if (txd->txdw5 & htole32(R92C_TXDW5_SGI))
		flags |= IEEE80211_RADIOTAP_F_SHORTGI;
	return (flags);
}