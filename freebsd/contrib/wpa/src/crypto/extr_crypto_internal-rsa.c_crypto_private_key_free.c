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
struct crypto_rsa_key {int dummy; } ;
struct crypto_private_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_rsa_free (struct crypto_rsa_key*) ; 

void crypto_private_key_free(struct crypto_private_key *key)
{
	crypto_rsa_free((struct crypto_rsa_key *) key);
}