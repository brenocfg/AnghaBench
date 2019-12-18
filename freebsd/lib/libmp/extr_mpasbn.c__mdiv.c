#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  bn; } ;
typedef  TYPE_1__ MINT ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_ERRCHECK (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_div (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  _bnerr (char const*) ; 
 int /*<<< orphan*/  _moveb (char const*,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
_mdiv(const char *msg, const MINT *nmp, const MINT *dmp, MINT *qmp, MINT *rmp,
    BN_CTX *c)
{
	BIGNUM *q, *r;

	q = NULL;
	r = BN_new();
	if (r != NULL)
		q = BN_new();
	if (r == NULL || q == NULL)
		_bnerr(msg);
	BN_ERRCHECK(msg, BN_div(q, r, nmp->bn, dmp->bn, c));
	_moveb(msg, q, qmp);
	_moveb(msg, r, rmp);
	BN_free(q);
	BN_free(r);
}