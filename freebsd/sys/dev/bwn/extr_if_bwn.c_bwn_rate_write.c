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
typedef  int uint16_t ;
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_SHARED ; 
 int bwn_plcp_getcck (int) ; 
 int bwn_plcp_getofdm (int) ; 
 int /*<<< orphan*/  bwn_shm_read_2 (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bwn_shm_write_2 (struct bwn_mac*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bwn_rate_write(struct bwn_mac *mac, uint16_t rate, int ofdm)
{
	uint16_t offset;

	if (ofdm) {
		offset = 0x480;
		offset += (bwn_plcp_getofdm(rate) & 0x000f) * 2;
	} else {
		offset = 0x4c0;
		offset += (bwn_plcp_getcck(rate) & 0x000f) * 2;
	}
	bwn_shm_write_2(mac, BWN_SHARED, offset + 0x20,
	    bwn_shm_read_2(mac, BWN_SHARED, offset));
}