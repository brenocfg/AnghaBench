#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * bn; } ;
typedef  TYPE_1__ MINT ;

/* Variables and functions */
 int /*<<< orphan*/  BN_ERRCHECK (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_hex2bn (int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  MPERR (char*) ; 
 int /*<<< orphan*/  _bnerr (char const*) ; 
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static MINT *
_xtom(const char *msg, const char *s)
{
	MINT *mp;

	mp = malloc(sizeof(*mp));
	if (mp == NULL)
		MPERR(("%s", msg));
	mp->bn = BN_new();
	if (mp->bn == NULL)
		_bnerr(msg);
	BN_ERRCHECK(msg, BN_hex2bn(&mp->bn, s));
	return (mp);
}