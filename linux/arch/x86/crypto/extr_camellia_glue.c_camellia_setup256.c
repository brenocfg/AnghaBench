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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  CAMELLIA_F (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA1L ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA1R ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA2L ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA2R ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA3L ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA3R ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA4L ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA4R ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA5L ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA5R ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA6L ; 
 int /*<<< orphan*/  CAMELLIA_SIGMA6R ; 
 int /*<<< orphan*/  ROLDQ (int,int,int) ; 
 int /*<<< orphan*/  camellia_setup_tail (int*,int*,int) ; 
 int get_unaligned_be64 (unsigned char const*) ; 

__attribute__((used)) static void camellia_setup256(const unsigned char *key, u64 *subkey)
{
	u64 kl, kr;			/* left half of key */
	u64 krl, krr;			/* right half of key */
	u64 ww;				/* temporary variables */
	u64 subRL[34];

	/**
	 *  key = (kl || kr || krl || krr) (|| is concatenation)
	 */
	kl = get_unaligned_be64(key);
	kr = get_unaligned_be64(key + 8);
	krl = get_unaligned_be64(key + 16);
	krr = get_unaligned_be64(key + 24);

	/* generate KL dependent subkeys */
	/* kw1 */
	subRL[0] = kl;
	/* kw2 */
	subRL[1] = kr;
	ROLDQ(kl, kr, 45);
	/* k9 */
	subRL[12] = kl;
	/* k10 */
	subRL[13] = kr;
	ROLDQ(kl, kr, 15);
	/* kl3 */
	subRL[16] = kl;
	/* kl4 */
	subRL[17] = kr;
	ROLDQ(kl, kr, 17);
	/* k17 */
	subRL[22] = kl;
	/* k18 */
	subRL[23] = kr;
	ROLDQ(kl, kr, 34);
	/* k23 */
	subRL[30] = kl;
	/* k24 */
	subRL[31] = kr;

	/* generate KR dependent subkeys */
	ROLDQ(krl, krr, 15);
	/* k3 */
	subRL[4] = krl;
	/* k4 */
	subRL[5] = krr;
	ROLDQ(krl, krr, 15);
	/* kl1 */
	subRL[8] = krl;
	/* kl2 */
	subRL[9] = krr;
	ROLDQ(krl, krr, 30);
	/* k13 */
	subRL[18] = krl;
	/* k14 */
	subRL[19] = krr;
	ROLDQ(krl, krr, 34);
	/* k19 */
	subRL[26] = krl;
	/* k20 */
	subRL[27] = krr;
	ROLDQ(krl, krr, 34);

	/* generate KA */
	kl = subRL[0] ^ krl;
	kr = subRL[1] ^ krr;

	CAMELLIA_F(kl, CAMELLIA_SIGMA1L, CAMELLIA_SIGMA1R, ww);
	kr ^= ww;
	CAMELLIA_F(kr, CAMELLIA_SIGMA2L, CAMELLIA_SIGMA2R, kl);
	kl ^= krl;
	CAMELLIA_F(kl, CAMELLIA_SIGMA3L, CAMELLIA_SIGMA3R, kr);
	kr ^= ww ^ krr;
	CAMELLIA_F(kr, CAMELLIA_SIGMA4L, CAMELLIA_SIGMA4R, ww);
	kl ^= ww;

	/* generate KB */
	krl ^= kl;
	krr ^= kr;
	CAMELLIA_F(krl, CAMELLIA_SIGMA5L, CAMELLIA_SIGMA5R, ww);
	krr ^= ww;
	CAMELLIA_F(krr, CAMELLIA_SIGMA6L, CAMELLIA_SIGMA6R, ww);
	krl ^= ww;

	/* generate KA dependent subkeys */
	ROLDQ(kl, kr, 15);
	/* k5 */
	subRL[6] = kl;
	/* k6 */
	subRL[7] = kr;
	ROLDQ(kl, kr, 30);
	/* k11 */
	subRL[14] = kl;
	/* k12 */
	subRL[15] = kr;
	/* rotation left shift 32bit */
	ROLDQ(kl, kr, 32);
	/* kl5 */
	subRL[24] = kl;
	/* kl6 */
	subRL[25] = kr;
	/* rotation left shift 17 from k11,k12 -> k21,k22 */
	ROLDQ(kl, kr, 17);
	/* k21 */
	subRL[28] = kl;
	/* k22 */
	subRL[29] = kr;

	/* generate KB dependent subkeys */
	/* k1 */
	subRL[2] = krl;
	/* k2 */
	subRL[3] = krr;
	ROLDQ(krl, krr, 30);
	/* k7 */
	subRL[10] = krl;
	/* k8 */
	subRL[11] = krr;
	ROLDQ(krl, krr, 30);
	/* k15 */
	subRL[20] = krl;
	/* k16 */
	subRL[21] = krr;
	ROLDQ(krl, krr, 51);
	/* kw3 */
	subRL[32] = krl;
	/* kw4 */
	subRL[33] = krr;

	camellia_setup_tail(subkey, subRL, 32);
}