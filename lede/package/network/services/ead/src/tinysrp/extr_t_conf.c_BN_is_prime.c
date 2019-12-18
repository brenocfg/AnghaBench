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
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int BN_is_prime_fasttest (int /*<<< orphan*/  const*,int,void (*) (int,int,void*),int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 

int BN_is_prime(const BIGNUM *a, int checks, void (*callback)(int,int,void *),
	BN_CTX *ctx_passed, void *cb_arg)
	{
	return BN_is_prime_fasttest(a, checks, callback, ctx_passed, cb_arg, 0);
	}