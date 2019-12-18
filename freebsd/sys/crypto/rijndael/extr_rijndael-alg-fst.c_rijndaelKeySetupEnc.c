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
typedef  int u32 ;
typedef  size_t temp ;

/* Variables and functions */
 int GETU32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int* Te4 ; 
 int* rcon ; 

int rijndaelKeySetupEnc(u32 rk[/*4*(Nr + 1)*/], const u8 cipherKey[], int keyBits) {
   	int i = 0;
	u32 temp;

	KASSERT(keyBits == 128 || keyBits == 192 || keyBits == 256,
	    ("Invalid key size (%d).", keyBits));
	rk[0] = GETU32(cipherKey     );
	rk[1] = GETU32(cipherKey +  4);
	rk[2] = GETU32(cipherKey +  8);
	rk[3] = GETU32(cipherKey + 12);
	if (keyBits == 128) {
		for (;;) {
			temp  = rk[3];
			rk[4] = rk[0] ^
				(Te4[(temp >> 16) & 0xff] & 0xff000000) ^
				(Te4[(temp >>  8) & 0xff] & 0x00ff0000) ^
				(Te4[(temp      ) & 0xff] & 0x0000ff00) ^
				(Te4[(temp >> 24)       ] & 0x000000ff) ^
				rcon[i];
			rk[5] = rk[1] ^ rk[4];
			rk[6] = rk[2] ^ rk[5];
			rk[7] = rk[3] ^ rk[6];
			if (++i == 10) {
				return 10;
			}
			rk += 4;
		}
	}
	rk[4] = GETU32(cipherKey + 16);
	rk[5] = GETU32(cipherKey + 20);
	if (keyBits == 192) {
		for (;;) {
			temp = rk[ 5];
			rk[ 6] = rk[ 0] ^
				(Te4[(temp >> 16) & 0xff] & 0xff000000) ^
				(Te4[(temp >>  8) & 0xff] & 0x00ff0000) ^
				(Te4[(temp      ) & 0xff] & 0x0000ff00) ^
				(Te4[(temp >> 24)       ] & 0x000000ff) ^
				rcon[i];
			rk[ 7] = rk[ 1] ^ rk[ 6];
			rk[ 8] = rk[ 2] ^ rk[ 7];
			rk[ 9] = rk[ 3] ^ rk[ 8];
			if (++i == 8) {
				return 12;
			}
			rk[10] = rk[ 4] ^ rk[ 9];
			rk[11] = rk[ 5] ^ rk[10];
			rk += 6;
		}
	}
	rk[6] = GETU32(cipherKey + 24);
	rk[7] = GETU32(cipherKey + 28);
	if (keyBits == 256) {
        for (;;) {
        	temp = rk[ 7];
        	rk[ 8] = rk[ 0] ^
        		(Te4[(temp >> 16) & 0xff] & 0xff000000) ^
        		(Te4[(temp >>  8) & 0xff] & 0x00ff0000) ^
        		(Te4[(temp      ) & 0xff] & 0x0000ff00) ^
        		(Te4[(temp >> 24)       ] & 0x000000ff) ^
        		rcon[i];
        	rk[ 9] = rk[ 1] ^ rk[ 8];
        	rk[10] = rk[ 2] ^ rk[ 9];
        	rk[11] = rk[ 3] ^ rk[10];
			if (++i == 7) {
				return 14;
			}
        	temp = rk[11];
        	rk[12] = rk[ 4] ^
        		(Te4[(temp >> 24)       ] & 0xff000000) ^
        		(Te4[(temp >> 16) & 0xff] & 0x00ff0000) ^
        		(Te4[(temp >>  8) & 0xff] & 0x0000ff00) ^
        		(Te4[(temp      ) & 0xff] & 0x000000ff);
        	rk[13] = rk[ 5] ^ rk[12];
        	rk[14] = rk[ 6] ^ rk[13];
        	rk[15] = rk[ 7] ^ rk[14];

			rk += 8;
        }
	}
	return 0;
}