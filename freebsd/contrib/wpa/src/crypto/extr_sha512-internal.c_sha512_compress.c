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
typedef  scalar_t__ u64 ;
struct sha512_state {scalar_t__* state; } ;

/* Variables and functions */
 scalar_t__ Ch (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ Gamma0 (scalar_t__) ; 
 scalar_t__ Gamma1 (scalar_t__) ; 
 scalar_t__* K ; 
 scalar_t__ Maj (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ Sigma0 (scalar_t__) ; 
 scalar_t__ Sigma1 (scalar_t__) ; 
 scalar_t__ WPA_GET_BE64 (unsigned char*) ; 
 int /*<<< orphan*/  os_free (scalar_t__*) ; 
 scalar_t__* os_malloc (int) ; 

__attribute__((used)) static int sha512_compress(struct sha512_state *md, unsigned char *buf)
{
	u64 S[8], t0, t1;
	u64 *W;
	int i;

	W = os_malloc(80 * sizeof(u64));
	if (!W)
		return -1;

	/* copy state into S */
	for (i = 0; i < 8; i++) {
		S[i] = md->state[i];
	}

	/* copy the state into 1024-bits into W[0..15] */
	for (i = 0; i < 16; i++)
		W[i] = WPA_GET_BE64(buf + (8 * i));

	/* fill W[16..79] */
	for (i = 16; i < 80; i++) {
		W[i] = Gamma1(W[i - 2]) + W[i - 7] + Gamma0(W[i - 15]) +
			W[i - 16];
	}

	/* Compress */
	for (i = 0; i < 80; i++) {
		t0 = S[7] + Sigma1(S[4]) + Ch(S[4], S[5], S[6]) + K[i] + W[i];
		t1 = Sigma0(S[0]) + Maj(S[0], S[1], S[2]);
		S[7] = S[6];
		S[6] = S[5];
		S[5] = S[4];
		S[4] = S[3] + t0;
		S[3] = S[2];
		S[2] = S[1];
		S[1] = S[0];
		S[0] = t0 + t1;
	}

	/* feedback */
	for (i = 0; i < 8; i++) {
		md->state[i] = md->state[i] + S[i];
	}

	os_free(W);
	return 0;
}