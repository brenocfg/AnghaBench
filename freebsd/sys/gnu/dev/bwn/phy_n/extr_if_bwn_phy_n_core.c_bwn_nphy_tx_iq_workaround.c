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
typedef  int /*<<< orphan*/  uint16_t ;
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_NTAB16 (int,int) ; 
 int /*<<< orphan*/  BWN_SHARED ; 
 int /*<<< orphan*/  BWN_SHM_SH_NPHY_TXIQW0 ; 
 int /*<<< orphan*/  BWN_SHM_SH_NPHY_TXIQW1 ; 
 int /*<<< orphan*/  BWN_SHM_SH_NPHY_TXIQW2 ; 
 int /*<<< orphan*/  BWN_SHM_SH_NPHY_TXIQW3 ; 
 int /*<<< orphan*/  bwn_ntab_read_bulk (struct bwn_mac*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bwn_shm_write_2 (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bwn_nphy_tx_iq_workaround(struct bwn_mac *mac)
{
	uint16_t array[4];
	bwn_ntab_read_bulk(mac, BWN_NTAB16(0xF, 0x50), 4, array);

	bwn_shm_write_2(mac, BWN_SHARED, BWN_SHM_SH_NPHY_TXIQW0, array[0]);
	bwn_shm_write_2(mac, BWN_SHARED, BWN_SHM_SH_NPHY_TXIQW1, array[1]);
	bwn_shm_write_2(mac, BWN_SHARED, BWN_SHM_SH_NPHY_TXIQW2, array[2]);
	bwn_shm_write_2(mac, BWN_SHARED, BWN_SHM_SH_NPHY_TXIQW3, array[3]);
}