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

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/ * default_cipher_testvec_configs ; 
 int /*<<< orphan*/ * default_hash_testvec_configs ; 
 int /*<<< orphan*/  valid_testvec_config (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void alg_check_testvec_configs(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(default_cipher_testvec_configs); i++)
		WARN_ON(!valid_testvec_config(
				&default_cipher_testvec_configs[i]));

	for (i = 0; i < ARRAY_SIZE(default_hash_testvec_configs); i++)
		WARN_ON(!valid_testvec_config(
				&default_hash_testvec_configs[i]));
}