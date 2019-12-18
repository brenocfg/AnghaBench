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
typedef  int u8 ;
typedef  int /*<<< orphan*/  symmetric_key ;

/* Variables and functions */
 int /*<<< orphan*/  des_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  des_ecb_encrypt (int const*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  des_setup (int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int des_encrypt(const u8 *clear, const u8 *key, u8 *cypher)
{
	u8 pkey[8], next, tmp;
	int i;
	symmetric_key skey;

	/* Add parity bits to the key */
	next = 0;
	for (i = 0; i < 7; i++) {
		tmp = key[i];
		pkey[i] = (tmp >> i) | next | 1;
		next = tmp << (7 - i);
	}
	pkey[i] = next | 1;

	des_setup(pkey, 8, 0, &skey);
	des_ecb_encrypt(clear, cypher, &skey);
	des_done(&skey);
	return 0;
}