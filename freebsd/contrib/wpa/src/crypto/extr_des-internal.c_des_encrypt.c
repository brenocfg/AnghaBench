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
typedef  int u32 ;
typedef  int /*<<< orphan*/  pkey ;
typedef  int /*<<< orphan*/  ek ;

/* Variables and functions */
 int WPA_GET_BE32 (int const*) ; 
 int /*<<< orphan*/  WPA_PUT_BE32 (int*,int) ; 
 int /*<<< orphan*/  desfunc (int*,int*) ; 
 int /*<<< orphan*/  deskey (int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  os_memset (int*,int /*<<< orphan*/ ,int) ; 

int des_encrypt(const u8 *clear, const u8 *key, u8 *cypher)
{
	u8 pkey[8], next, tmp;
	int i;
	u32 ek[32], work[2];

	/* Add parity bits to the key */
	next = 0;
	for (i = 0; i < 7; i++) {
		tmp = key[i];
		pkey[i] = (tmp >> i) | next | 1;
		next = tmp << (7 - i);
	}
	pkey[i] = next | 1;

	deskey(pkey, 0, ek);

	work[0] = WPA_GET_BE32(clear);
	work[1] = WPA_GET_BE32(clear + 4);
	desfunc(work, ek);
	WPA_PUT_BE32(cypher, work[0]);
	WPA_PUT_BE32(cypher + 4, work[1]);

	os_memset(pkey, 0, sizeof(pkey));
	os_memset(ek, 0, sizeof(ek));
	return 0;
}