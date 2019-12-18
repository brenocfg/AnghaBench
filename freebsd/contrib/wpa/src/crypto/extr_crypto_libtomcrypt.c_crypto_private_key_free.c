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
struct crypto_private_key {int /*<<< orphan*/  rsa; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct crypto_private_key*) ; 
 int /*<<< orphan*/  rsa_free (int /*<<< orphan*/ *) ; 

void crypto_private_key_free(struct crypto_private_key *key)
{
	if (key) {
		rsa_free(&key->rsa);
		os_free(key);
	}
}