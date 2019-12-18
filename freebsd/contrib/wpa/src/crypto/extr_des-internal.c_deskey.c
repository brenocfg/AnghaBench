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

/* Variables and functions */
 int* bigbyte ; 
 int const* bytebit ; 
 int /*<<< orphan*/  cookey (int*,int*) ; 
 scalar_t__* pc1 ; 
 scalar_t__* pc2 ; 
 scalar_t__* totrot ; 

__attribute__((used)) static void deskey(const u8 *key, int decrypt, u32 *keyout)
{
	u32 i, j, l, m, n, kn[32];
	u8 pc1m[56], pcr[56];

	for (j = 0; j < 56; j++) {
		l = (u32) pc1[j];
		m = l & 7;
		pc1m[j] = (u8)
			((key[l >> 3U] & bytebit[m]) == bytebit[m] ? 1 : 0);
	}

	for (i = 0; i < 16; i++) {
		if (decrypt)
			m = (15 - i) << 1;
		else
			m = i << 1;
		n = m + 1;
		kn[m] = kn[n] = 0L;
		for (j = 0; j < 28; j++) {
			l = j + (u32) totrot[i];
			if (l < 28)
				pcr[j] = pc1m[l];
			else
				pcr[j] = pc1m[l - 28];
		}
		for (/* j = 28 */; j < 56; j++) {
			l = j + (u32) totrot[i];
			if (l < 56)
				pcr[j] = pc1m[l];
			else
				pcr[j] = pc1m[l - 28];
		}
		for (j = 0; j < 24; j++) {
			if ((int) pcr[(int) pc2[j]] != 0)
				kn[m] |= bigbyte[j];
			if ((int) pcr[(int) pc2[j + 24]] != 0)
				kn[n] |= bigbyte[j];
		}
	}

	cookey(kn, keyout);
}