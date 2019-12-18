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
typedef  int* ntlm_des_block ;

/* Variables and functions */
 int EVEN_PARITY (int) ; 

__attribute__((used)) static void generate_odd_parity(ntlm_des_block *block)
{
	size_t i;

	for (i = 0; i < sizeof(ntlm_des_block); i++)
		(*block)[i] |= (1 ^ EVEN_PARITY((*block)[i]));
}