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
struct sshkey {struct sshkey* dsa; } ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_PTR_NE (struct sshkey*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSA_get0_key (struct sshkey*,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 

const BIGNUM *
dsa_pub_key(struct sshkey *k)
{
	const BIGNUM *pub_key = NULL;

	ASSERT_PTR_NE(k, NULL);
	ASSERT_PTR_NE(k->dsa, NULL);
	DSA_get0_key(k->dsa, &pub_key, NULL);
	return pub_key;
}