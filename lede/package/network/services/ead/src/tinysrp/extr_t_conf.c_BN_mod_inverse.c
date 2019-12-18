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
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_add (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * BN_copy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_div (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_is_one (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_is_zero (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_mod (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mul (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* BN_new () ; 
 int /*<<< orphan*/  BN_one (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_sub (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/  const*) ; 

BIGNUM *BN_mod_inverse(BIGNUM *in, BIGNUM *a, const BIGNUM *n, BN_CTX *ctx)
	{
	BIGNUM *A,*B,*X,*Y,*M,*D,*R=NULL;
	BIGNUM *T,*ret=NULL;
	int sign;

	bn_check_top(a);
	bn_check_top(n);

	BN_CTX_start(ctx);
	A = BN_CTX_get(ctx);
	B = BN_CTX_get(ctx);
	X = BN_CTX_get(ctx);
	D = BN_CTX_get(ctx);
	M = BN_CTX_get(ctx);
	Y = BN_CTX_get(ctx);
	if (Y == NULL) goto err;

	if (in == NULL)
		R=BN_new();
	else
		R=in;
	if (R == NULL) goto err;

	BN_zero(X);
	BN_one(Y);
	if (BN_copy(A,a) == NULL) goto err;
	if (BN_copy(B,n) == NULL) goto err;
	sign=1;

	while (!BN_is_zero(B))
		{
		if (!BN_div(D,M,A,B,ctx)) goto err;
		T=A;
		A=B;
		B=M;
		/* T has a struct, M does not */

		if (!BN_mul(T,D,X,ctx)) goto err;
		if (!BN_add(T,T,Y)) goto err;
		M=Y;
		Y=X;
		X=T;
		sign= -sign;
		}
	if (sign < 0)
		{
		if (!BN_sub(Y,n,Y)) goto err;
		}

	if (BN_is_one(A))
		{ if (!BN_mod(R,Y,n,ctx)) goto err; }
	else
		{
		goto err;
		}
	ret=R;
err:
	if ((ret == NULL) && (in == NULL)) BN_free(R);
	BN_CTX_end(ctx);
	return(ret);
	}