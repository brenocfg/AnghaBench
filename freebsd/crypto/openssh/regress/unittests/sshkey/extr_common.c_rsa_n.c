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
struct sshkey {struct sshkey* rsa; } ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_PTR_NE (struct sshkey*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_get0_key (struct sshkey*,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

const BIGNUM *
rsa_n(struct sshkey *k)
{
	const BIGNUM *n = NULL;

	ASSERT_PTR_NE(k, NULL);
	ASSERT_PTR_NE(k->rsa, NULL);
	RSA_get0_key(k->rsa, &n, NULL, NULL);
	return n;
}