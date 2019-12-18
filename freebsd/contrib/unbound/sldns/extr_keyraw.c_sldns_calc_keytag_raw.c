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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 scalar_t__ LDNS_RSAMD5 ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

uint16_t sldns_calc_keytag_raw(uint8_t* key, size_t keysize)
{
	if(keysize < 4) {
		return 0;
	}
	/* look at the algorithm field, copied from 2535bis */
	if (key[3] == LDNS_RSAMD5) {
		uint16_t ac16 = 0;
		if (keysize > 4) {
			memmove(&ac16, key + keysize - 3, 2);
		}
		ac16 = ntohs(ac16);
		return (uint16_t) ac16;
	} else {
		size_t i;
		uint32_t ac32 = 0;
		for (i = 0; i < keysize; ++i) {
			ac32 += (i & 1) ? key[i] : key[i] << 8;
		}
		ac32 += (ac32 >> 16) & 0xFFFF;
		return (uint16_t) (ac32 & 0xFFFF);
	}
}