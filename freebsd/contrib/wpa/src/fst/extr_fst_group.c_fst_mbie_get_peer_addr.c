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
typedef  int /*<<< orphan*/  u8 ;
struct multi_band_ie {int mb_ctrl; int /*<<< orphan*/  len; int /*<<< orphan*/ * bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int MB_CTRL_ROLE (int) ; 
 int MB_CTRL_STA_MAC_PRESENT ; 
#define  MB_STA_ROLE_AP 129 
#define  MB_STA_ROLE_NON_PCP_NON_AP 128 

__attribute__((used)) static const u8 * fst_mbie_get_peer_addr(const struct multi_band_ie *mbie)
{
	const u8 *peer_addr = NULL;

	switch (MB_CTRL_ROLE(mbie->mb_ctrl)) {
	case MB_STA_ROLE_AP:
		peer_addr = mbie->bssid;
		break;
	case MB_STA_ROLE_NON_PCP_NON_AP:
		if (mbie->mb_ctrl & MB_CTRL_STA_MAC_PRESENT &&
		    (size_t) 2 + mbie->len >= sizeof(*mbie) + ETH_ALEN)
			peer_addr = (const u8 *) &mbie[1];
		break;
	default:
		break;
	}

	return peer_addr;
}