#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  scalar_t__ hook_p ;
struct TYPE_5__ {scalar_t__ hook; } ;

/* Variables and functions */
 int EINVAL ; 
 int EISCONN ; 
 int /*<<< orphan*/  NGTLOCK (TYPE_1__* const) ; 
 int /*<<< orphan*/  NGTUNLOCK (TYPE_1__* const) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_TTY_HOOK ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ngt_newhook(node_p node, hook_p hook, const char *name)
{
	const sc_p sc = NG_NODE_PRIVATE(node);

	if (strcmp(name, NG_TTY_HOOK))
		return (EINVAL);

	if (sc->hook)
		return (EISCONN);

	NGTLOCK(sc);
	sc->hook = hook;
	NGTUNLOCK(sc);

	return (0);
}