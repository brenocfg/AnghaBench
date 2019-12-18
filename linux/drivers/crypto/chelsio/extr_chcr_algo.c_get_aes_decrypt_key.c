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
#define  AES_KEYLENGTH_128BIT 130 
#define  AES_KEYLENGTH_192BIT 129 
#define  AES_KEYLENGTH_256BIT 128 
 int KEYLENGTH_4BYTES ; 
 int KEYLENGTH_6BYTES ; 
 int KEYLENGTH_8BYTES ; 
 int MAX_NK ; 
 int NUMBER_OF_ROUNDS_10 ; 
 int NUMBER_OF_ROUNDS_12 ; 
 int NUMBER_OF_ROUNDS_14 ; 
 int aes_ks_subword (int) ; 
 int be32_to_cpu (int) ; 
 int htonl (int) ; 
 int* round_constant ; 

__attribute__((used)) static void get_aes_decrypt_key(unsigned char *dec_key,
				       const unsigned char *key,
				       unsigned int keylength)
{
	u32 temp;
	u32 w_ring[MAX_NK];
	int i, j, k;
	u8  nr, nk;

	switch (keylength) {
	case AES_KEYLENGTH_128BIT:
		nk = KEYLENGTH_4BYTES;
		nr = NUMBER_OF_ROUNDS_10;
		break;
	case AES_KEYLENGTH_192BIT:
		nk = KEYLENGTH_6BYTES;
		nr = NUMBER_OF_ROUNDS_12;
		break;
	case AES_KEYLENGTH_256BIT:
		nk = KEYLENGTH_8BYTES;
		nr = NUMBER_OF_ROUNDS_14;
		break;
	default:
		return;
	}
	for (i = 0; i < nk; i++)
		w_ring[i] = be32_to_cpu(*(u32 *)&key[4 * i]);

	i = 0;
	temp = w_ring[nk - 1];
	while (i + nk < (nr + 1) * 4) {
		if (!(i % nk)) {
			/* RotWord(temp) */
			temp = (temp << 8) | (temp >> 24);
			temp = aes_ks_subword(temp);
			temp ^= round_constant[i / nk];
		} else if (nk == 8 && (i % 4 == 0)) {
			temp = aes_ks_subword(temp);
		}
		w_ring[i % nk] ^= temp;
		temp = w_ring[i % nk];
		i++;
	}
	i--;
	for (k = 0, j = i % nk; k < nk; k++) {
		*((u32 *)dec_key + k) = htonl(w_ring[j]);
		j--;
		if (j < 0)
			j += nk;
	}
}