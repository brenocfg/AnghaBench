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
typedef  int /*<<< orphan*/  MINT ;
typedef  int /*<<< orphan*/  BN_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  _bnerr (char*) ; 
 int /*<<< orphan*/  _mdiv (char*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
mp_mdiv(const MINT *nmp, const MINT *dmp, MINT *qmp, MINT *rmp)
{
	BN_CTX *c;

	c = BN_CTX_new();
	if (c == NULL)
		_bnerr("mdiv");
	_mdiv("mdiv", nmp, dmp, qmp, rmp, c);
	BN_CTX_free(c);
}