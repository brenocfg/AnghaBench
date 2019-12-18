#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  bn; } ;
typedef  TYPE_1__ MINT ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_ERRCHECK (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_div (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  MPERR (char*) ; 
 int /*<<< orphan*/  _bnerr (char const*) ; 
 TYPE_1__* _itom (char const*,short) ; 
 int /*<<< orphan*/  _mfree (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  _moveb (char const*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 char* _mtox (char const*,TYPE_1__*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 short strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
_sdiv(const char *msg, const MINT *nmp, short d, MINT *qmp, short *ro,
    BN_CTX *c)
{
	MINT *dmp, *rmp;
	BIGNUM *q, *r;
	char *s;

	r = NULL;
	q = BN_new();
	if (q != NULL)
		r = BN_new();
	if (q == NULL || r == NULL)
		_bnerr(msg);
	dmp = _itom(msg, d);
	rmp = _itom(msg, 0);
	BN_ERRCHECK(msg, BN_div(q, r, nmp->bn, dmp->bn, c));
	_moveb(msg, q, qmp);
	_moveb(msg, r, rmp);
	s = _mtox(msg, rmp);
	errno = 0;
	*ro = strtol(s, NULL, 16);
	if (errno != 0)
		MPERR(("%s underflow or overflow", msg));
	free(s);
	_mfree(msg, dmp);
	_mfree(msg, rmp);
	BN_free(r);
	BN_free(q);
}