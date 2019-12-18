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
typedef  int u_int ;

/* Variables and functions */
 int RSS_KEYSIZE ; 

uint32_t
toeplitz_hash(u_int keylen, const uint8_t *key, u_int datalen,
    const uint8_t *data)
{
	uint32_t hash = 0, v;
	u_int i, b;

	/* XXXRW: Perhaps an assertion about key length vs. data length? */

	v = (key[0]<<24) + (key[1]<<16) + (key[2] <<8) + key[3];
	for (i = 0; i < datalen; i++) {
		for (b = 0; b < 8; b++) {
			if (data[i] & (1<<(7-b)))
				hash ^= v;
			v <<= 1;
			if ((i + 4) < RSS_KEYSIZE &&
			    (key[i+4] & (1<<(7-b))))
				v |= 1;
		}
	}
	return (hash);
}