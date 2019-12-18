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
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
struct bwn_mac {scalar_t__ mac_ktp; } ;

/* Variables and functions */
 int BWN_SEC_KEY2FW (struct bwn_mac*,int) ; 
 int BWN_SEC_KEYSIZE ; 
 int /*<<< orphan*/  BWN_SHARED ; 
 scalar_t__ BWN_SHARED_KEYIDX_BLOCK ; 
 int /*<<< orphan*/  bwn_shm_write_2 (struct bwn_mac*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void
bwn_key_write(struct bwn_mac *mac, uint8_t index, uint8_t algorithm,
    const uint8_t *key)
{
	unsigned int i;
	uint32_t offset;
	uint16_t kidx, value;

	kidx = BWN_SEC_KEY2FW(mac, index);
	bwn_shm_write_2(mac, BWN_SHARED,
	    BWN_SHARED_KEYIDX_BLOCK + (kidx * 2), (kidx << 4) | algorithm);

	offset = mac->mac_ktp + (index * BWN_SEC_KEYSIZE);
	for (i = 0; i < BWN_SEC_KEYSIZE; i += 2) {
		value = key[i];
		value |= (uint16_t)(key[i + 1]) << 8;
		bwn_shm_write_2(mac, BWN_SHARED, offset + i, value);
	}
}