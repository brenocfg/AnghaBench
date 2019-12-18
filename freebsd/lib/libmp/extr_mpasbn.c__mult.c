#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  bn; } ;
typedef  TYPE_1__ MINT ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_ERRCHECK (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  _bnerr (char const*) ; 
 int /*<<< orphan*/  _moveb (char const*,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
_mult(const char *msg, const MINT *mp1, const MINT *mp2, MINT *rmp, BN_CTX *c)
{
	BIGNUM *b;

	b = BN_new();
	if (b == NULL)
		_bnerr(msg);
	BN_ERRCHECK(msg, BN_mul(b, mp1->bn, mp2->bn, c));
	_moveb(msg, b, rmp);
	BN_free(b);
}