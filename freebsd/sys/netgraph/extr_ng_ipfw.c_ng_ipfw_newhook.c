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
typedef  scalar_t__ u_int16_t ;
typedef  int /*<<< orphan*/  node_p ;
typedef  TYPE_1__* hpriv_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_4__ {scalar_t__ rulenum; int /*<<< orphan*/  hook; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_NETGRAPH ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strtol (char const*,char**,int) ; 

__attribute__((used)) static int
ng_ipfw_newhook(node_p node, hook_p hook, const char *name)
{
	hpriv_p	hpriv;
	u_int16_t rulenum;
	const char *cp;
	char *endptr;

	/* Protect from leading zero */
	if (name[0] == '0' && name[1] != '\0')
		return (EINVAL);

	/* Check that name contains only digits */
	for (cp = name; *cp != '\0'; cp++)
		if (!isdigit(*cp))
			return (EINVAL);

	/* Convert it to integer */
	rulenum = (u_int16_t)strtol(name, &endptr, 10);
	if (*endptr != '\0')
		return (EINVAL);

	/* Allocate memory for this hook's private data */
	hpriv = malloc(sizeof(*hpriv), M_NETGRAPH, M_NOWAIT | M_ZERO);
	if (hpriv== NULL)
		return (ENOMEM);

	hpriv->hook = hook;
	hpriv->rulenum = rulenum;

	NG_HOOK_SET_PRIVATE(hook, hpriv);

	return(0);
}