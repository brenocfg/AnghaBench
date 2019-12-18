#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
struct ng_one2many_link {int /*<<< orphan*/  stats; int /*<<< orphan*/ * hook; } ;
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/ * hook_p ;
struct TYPE_5__ {int* enabledLinks; } ;
struct TYPE_6__ {TYPE_1__ conf; struct ng_one2many_link one; struct ng_one2many_link* many; } ;

/* Variables and functions */
 int EINVAL ; 
 int EISCONN ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (int /*<<< orphan*/ *,void*) ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_ONE2MANY_HOOK_MANY_PREFIX ; 
 int /*<<< orphan*/  NG_ONE2MANY_HOOK_ONE ; 
 scalar_t__ NG_ONE2MANY_MAX_LINKS ; 
 int NG_ONE2MANY_ONE_LINKNUM ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int /*<<< orphan*/  ng_one2many_update_many (TYPE_2__* const) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strtoul (char const*,char**,int) ; 

__attribute__((used)) static	int
ng_one2many_newhook(node_p node, hook_p hook, const char *name)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	struct ng_one2many_link *link;
	int linkNum;
	u_long i;

	/* Which hook? */
	if (strncmp(name, NG_ONE2MANY_HOOK_MANY_PREFIX,
	    strlen(NG_ONE2MANY_HOOK_MANY_PREFIX)) == 0) {
		const char *cp;
		char *eptr;

		cp = name + strlen(NG_ONE2MANY_HOOK_MANY_PREFIX);
		if (!isdigit(*cp) || (cp[0] == '0' && cp[1] != '\0'))
			return (EINVAL);
		i = strtoul(cp, &eptr, 10);
		if (*eptr != '\0' || i >= NG_ONE2MANY_MAX_LINKS)
			return (EINVAL);
		linkNum = (int)i;
		link = &priv->many[linkNum];
	} else if (strcmp(name, NG_ONE2MANY_HOOK_ONE) == 0) {
		linkNum = NG_ONE2MANY_ONE_LINKNUM;
		link = &priv->one;
	} else
		return (EINVAL);

	/* Is hook already connected? (should never happen) */
	if (link->hook != NULL)
		return (EISCONN);

	/* Setup private info for this link */
	NG_HOOK_SET_PRIVATE(hook, (void *)(intptr_t)linkNum);
	link->hook = hook;
	bzero(&link->stats, sizeof(link->stats));
	if (linkNum != NG_ONE2MANY_ONE_LINKNUM) {
		priv->conf.enabledLinks[linkNum] = 1;	/* auto-enable link */
		ng_one2many_update_many(priv);
	}

	/* Done */
	return (0);
}