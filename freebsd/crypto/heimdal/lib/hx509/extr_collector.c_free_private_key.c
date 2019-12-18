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
struct private_key {int /*<<< orphan*/  localKeyId; scalar_t__ private_key; int /*<<< orphan*/  alg; } ;

/* Variables and functions */
 int /*<<< orphan*/  der_free_octet_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct private_key*) ; 
 int /*<<< orphan*/  free_AlgorithmIdentifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hx509_private_key_free (scalar_t__*) ; 

__attribute__((used)) static void
free_private_key(struct private_key *key)
{
    free_AlgorithmIdentifier(&key->alg);
    if (key->private_key)
	hx509_private_key_free(&key->private_key);
    der_free_octet_string(&key->localKeyId);
    free(key);
}