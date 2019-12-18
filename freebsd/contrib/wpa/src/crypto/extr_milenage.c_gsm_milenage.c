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

/* Variables and functions */
 scalar_t__ milenage_f2345 (int const*,int const*,int const*,int*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int*,int*,int) ; 

int gsm_milenage(const u8 *opc, const u8 *k, const u8 *_rand, u8 *sres, u8 *kc)
{
	u8 res[8], ck[16], ik[16];
	int i;

	if (milenage_f2345(opc, k, _rand, res, ck, ik, NULL, NULL))
		return -1;

	for (i = 0; i < 8; i++)
		kc[i] = ck[i] ^ ck[i + 8] ^ ik[i] ^ ik[i + 8];

#ifdef GSM_MILENAGE_ALT_SRES
	os_memcpy(sres, res, 4);
#else /* GSM_MILENAGE_ALT_SRES */
	for (i = 0; i < 4; i++)
		sres[i] = res[i] ^ res[i + 4];
#endif /* GSM_MILENAGE_ALT_SRES */
	return 0;
}