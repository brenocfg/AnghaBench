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
typedef  int /*<<< orphan*/ * ntlm_des_block ;

/* Variables and functions */
 int /*<<< orphan*/  des_key_from_password (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void des_keys_from_lm_hash(ntlm_des_block out[3], ntlm_des_block lm_hash[2])
{
	ntlm_des_block split[3];

	memcpy(&split[0][0], &lm_hash[0][0], 7);

	memcpy(&split[1][0], &lm_hash[0][7], 1);
	memcpy(&split[1][1], &lm_hash[1][0], 6);

	memcpy(&split[2][0], &lm_hash[1][6], 2);

	des_key_from_password(&out[0], split[0], 7);
	des_key_from_password(&out[1], split[1], 7);
	des_key_from_password(&out[2], split[2], 2);
}