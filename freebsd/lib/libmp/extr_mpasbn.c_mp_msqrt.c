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
typedef  int /*<<< orphan*/  const MINT ;
typedef  int /*<<< orphan*/  BN_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  _bnerr (char*) ; 
 int /*<<< orphan*/  const* _itom (char*,int) ; 
 int /*<<< orphan*/  _madd (char*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int _mcmpa (char*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  _mdiv (char*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _mfree (char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  _movem (char*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  _msub (char*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  _mult (char*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _sdiv (char*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,short*,int /*<<< orphan*/ *) ; 

void
mp_msqrt(const MINT *nmp, MINT *xmp, MINT *rmp)
{
	BN_CTX *c;
	MINT *tolerance;
	MINT *ox, *x;
	MINT *z1, *z2, *z3;
	short i;

	c = BN_CTX_new();
	if (c == NULL)
		_bnerr("msqrt");
	tolerance = _itom("msqrt", 1);
	x = _itom("msqrt", 1);
	ox = _itom("msqrt", 0);
	z1 = _itom("msqrt", 0);
	z2 = _itom("msqrt", 0);
	z3 = _itom("msqrt", 0);
	do {
		_movem("msqrt", x, ox);
		_mdiv("msqrt", nmp, x, z1, z2, c);
		_madd("msqrt", x, z1, z2);
		_sdiv("msqrt", z2, 2, x, &i, c);
		_msub("msqrt", ox, x, z3);
	} while (_mcmpa("msqrt", z3, tolerance) == 1);
	_movem("msqrt", x, xmp);
	_mult("msqrt", x, x, z1, c);
	_msub("msqrt", nmp, z1, z2);
	_movem("msqrt", z2, rmp);
	_mfree("msqrt", tolerance);
	_mfree("msqrt", ox);
	_mfree("msqrt", x);
	_mfree("msqrt", z1);
	_mfree("msqrt", z2);
	_mfree("msqrt", z3);
	BN_CTX_free(c);
}