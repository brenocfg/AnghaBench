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

/* Variables and functions */
 int /*<<< orphan*/  EAP_SIM_MK_LEN ; 
 int fips186_2_prf (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int eap_sim_prf(const u8 *key, u8 *x, size_t xlen)
{
	return fips186_2_prf(key, EAP_SIM_MK_LEN, x, xlen);
}