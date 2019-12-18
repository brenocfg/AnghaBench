#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* dtpv_name; } ;
typedef  TYPE_1__ dtrace_provider_t ;
struct TYPE_6__ {char* dtpr_mod; char* dtpr_func; char* dtpr_name; TYPE_1__* dtpr_provider; } ;
typedef  TYPE_2__ dtrace_probe_t ;
struct TYPE_7__ {TYPE_2__* dte_probe; } ;
typedef  TYPE_3__ dtrace_ecb_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DTRACE_FULLNAMELEN ; 
 int /*<<< orphan*/  KDB_WHY_DTRACE ; 
 int NBBY ; 
 int /*<<< orphan*/  debug_enter (char*) ; 
 scalar_t__ dtrace_destructive_disallow ; 
 int /*<<< orphan*/  kdb_enter (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
dtrace_action_breakpoint(dtrace_ecb_t *ecb)
{
	dtrace_probe_t *probe = ecb->dte_probe;
	dtrace_provider_t *prov = probe->dtpr_provider;
	char c[DTRACE_FULLNAMELEN + 80], *str;
	char *msg = "dtrace: breakpoint action at probe ";
	char *ecbmsg = " (ecb ";
	uintptr_t mask = (0xf << (sizeof (uintptr_t) * NBBY / 4));
	uintptr_t val = (uintptr_t)ecb;
	int shift = (sizeof (uintptr_t) * NBBY) - 4, i = 0;

	if (dtrace_destructive_disallow)
		return;

	/*
	 * It's impossible to be taking action on the NULL probe.
	 */
	ASSERT(probe != NULL);

	/*
	 * This is a poor man's (destitute man's?) sprintf():  we want to
	 * print the provider name, module name, function name and name of
	 * the probe, along with the hex address of the ECB with the breakpoint
	 * action -- all of which we must place in the character buffer by
	 * hand.
	 */
	while (*msg != '\0')
		c[i++] = *msg++;

	for (str = prov->dtpv_name; *str != '\0'; str++)
		c[i++] = *str;
	c[i++] = ':';

	for (str = probe->dtpr_mod; *str != '\0'; str++)
		c[i++] = *str;
	c[i++] = ':';

	for (str = probe->dtpr_func; *str != '\0'; str++)
		c[i++] = *str;
	c[i++] = ':';

	for (str = probe->dtpr_name; *str != '\0'; str++)
		c[i++] = *str;

	while (*ecbmsg != '\0')
		c[i++] = *ecbmsg++;

	while (shift >= 0) {
		mask = (uintptr_t)0xf << shift;

		if (val >= ((uintptr_t)1 << shift))
			c[i++] = "0123456789abcdef"[(val & mask) >> shift];
		shift -= 4;
	}

	c[i++] = ')';
	c[i] = '\0';

#ifdef illumos
	debug_enter(c);
#else
	kdb_enter(KDB_WHY_DTRACE, "breakpoint action");
#endif
}