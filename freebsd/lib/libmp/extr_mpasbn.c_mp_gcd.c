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
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_ERRCHECK (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_gcd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  _bnerr (char*) ; 
 int /*<<< orphan*/  _moveb (char*,int /*<<< orphan*/ *,TYPE_1__*) ; 

void
mp_gcd(const MINT *mp1, const MINT *mp2, MINT *rmp)
{
	BIGNUM *b;
	BN_CTX *c;

	b = NULL;
	c = BN_CTX_new();
	if (c != NULL)
		b = BN_new();
	if (c == NULL || b == NULL)
		_bnerr("gcd");
	BN_ERRCHECK("gcd", BN_gcd(b, mp1->bn, mp2->bn, c));
	_moveb("gcd", b, rmp);
	BN_free(b);
	BN_CTX_free(c);
}