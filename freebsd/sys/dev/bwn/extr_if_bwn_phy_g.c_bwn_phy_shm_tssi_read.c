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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int BWN_HF_4DB_CCK_POWERBOOST ; 
 int /*<<< orphan*/  BWN_SHARED ; 
 int /*<<< orphan*/  BWN_SHARED_HFLO ; 
 scalar_t__ BWN_SHARED_TSSI_CCK ; 
 unsigned int BWN_TSSI_MAX ; 
 int ENOENT ; 
 int bwn_shm_read_2 (struct bwn_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bwn_shm_read_4 (struct bwn_mac*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bwn_shm_write_4 (struct bwn_mac*,int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 

__attribute__((used)) static int
bwn_phy_shm_tssi_read(struct bwn_mac *mac, uint16_t shm_offset)
{
	const uint8_t ofdm = (shm_offset != BWN_SHARED_TSSI_CCK);
	unsigned int a, b, c, d;
	unsigned int avg;
	uint32_t tmp;

	tmp = bwn_shm_read_4(mac, BWN_SHARED, shm_offset);
	a = tmp & 0xff;
	b = (tmp >> 8) & 0xff;
	c = (tmp >> 16) & 0xff;
	d = (tmp >> 24) & 0xff;
	if (a == 0 || a == BWN_TSSI_MAX || b == 0 || b == BWN_TSSI_MAX ||
	    c == 0 || c == BWN_TSSI_MAX || d == 0 || d == BWN_TSSI_MAX)
		return (ENOENT);
	bwn_shm_write_4(mac, BWN_SHARED, shm_offset,
	    BWN_TSSI_MAX | (BWN_TSSI_MAX << 8) |
	    (BWN_TSSI_MAX << 16) | (BWN_TSSI_MAX << 24));

	if (ofdm) {
		a = (a + 32) & 0x3f;
		b = (b + 32) & 0x3f;
		c = (c + 32) & 0x3f;
		d = (d + 32) & 0x3f;
	}

	avg = (a + b + c + d + 2) / 4;
	if (ofdm) {
		if (bwn_shm_read_2(mac, BWN_SHARED, BWN_SHARED_HFLO)
		    & BWN_HF_4DB_CCK_POWERBOOST)
			avg = (avg >= 13) ? (avg - 13) : 0;
	}
	return (avg);
}