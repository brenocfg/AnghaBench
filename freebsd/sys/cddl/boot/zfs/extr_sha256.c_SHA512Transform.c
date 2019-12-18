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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int BIGSIGMA0_512 (int) ; 
 int BIGSIGMA1_512 (int) ; 
 int Ch (int,int,int) ; 
 int Maj (int,int,int) ; 
 int* SHA512_K ; 
 int SIGMA0_512 (int) ; 
 int SIGMA1_512 (int) ; 

__attribute__((used)) static void
SHA512Transform(uint64_t *H, const uint8_t *cp)
{
	uint64_t a, b, c, d, e, f, g, h, t, T1, T2, W[80];

	/* copy chunk into the first 16 words of the message schedule */
	for (t = 0; t < 16; t++, cp += sizeof (uint64_t))
		W[t] = ((uint64_t)cp[0] << 56) | ((uint64_t)cp[1] << 48) |
		    ((uint64_t)cp[2] << 40) | ((uint64_t)cp[3] << 32) |
		    ((uint64_t)cp[4] << 24) | ((uint64_t)cp[5] << 16) |
		    ((uint64_t)cp[6] << 8) | (uint64_t)cp[7];

	/* extend the first 16 words into the remaining 64 words */
	for (t = 16; t < 80; t++)
		W[t] = SIGMA1_512(W[t - 2]) + W[t - 7] +
		    SIGMA0_512(W[t - 15]) + W[t - 16];

	/* init working variables to the current hash value */
	a = H[0]; b = H[1]; c = H[2]; d = H[3];
	e = H[4]; f = H[5]; g = H[6]; h = H[7];

	/* iterate the compression function for all rounds of the hash */
	for (t = 0; t < 80; t++) {
		T1 = h + BIGSIGMA1_512(e) + Ch(e, f, g) + SHA512_K[t] + W[t];
		T2 = BIGSIGMA0_512(a) + Maj(a, b, c);
		h = g; g = f; f = e; e = d + T1;
		d = c; c = b; b = a; a = T1 + T2;
	}

	/* add the compressed chunk to the current hash value */
	H[0] += a; H[1] += b; H[2] += c; H[3] += d;
	H[4] += e; H[5] += f; H[6] += g; H[7] += h;
}