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
typedef  int uint8_t ;
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_NPHY_RFSEQCA ; 
 int BWN_NPHY_RFSEQCA_RXEN ; 
 int BWN_NPHY_RFSEQCA_RXEN_SHIFT ; 
 int BWN_PHY_READ (struct bwn_mac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t bwn_nphy_get_rx_core_state(struct bwn_mac *mac)
{
	return (BWN_PHY_READ(mac, BWN_NPHY_RFSEQCA) & BWN_NPHY_RFSEQCA_RXEN) >>
		BWN_NPHY_RFSEQCA_RXEN_SHIFT;
}