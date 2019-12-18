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
 scalar_t__ milenage_f1 (int const*,int const*,int const*,int*,int*,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ milenage_f2345 (int const*,int const*,int const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ os_memcmp_const (int*,int const*,int) ; 

int milenage_auts(const u8 *opc, const u8 *k, const u8 *_rand, const u8 *auts,
		  u8 *sqn)
{
	u8 amf[2] = { 0x00, 0x00 }; /* TS 33.102 v7.0.0, 6.3.3 */
	u8 ak[6], mac_s[8];
	int i;

	if (milenage_f2345(opc, k, _rand, NULL, NULL, NULL, NULL, ak))
		return -1;
	for (i = 0; i < 6; i++)
		sqn[i] = auts[i] ^ ak[i];
	if (milenage_f1(opc, k, _rand, sqn, amf, NULL, mac_s) ||
	    os_memcmp_const(mac_s, auts + 6, 8) != 0)
		return -1;
	return 0;
}