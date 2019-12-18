#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/ * hook_p ;
struct TYPE_11__ {int /*<<< orphan*/  fn; int /*<<< orphan*/ * name; } ;
struct TYPE_9__ {int /*<<< orphan*/  enableMultilink; } ;
struct TYPE_10__ {int numActiveLinks; int /*<<< orphan*/ ** hooks; TYPE_3__ conf; TYPE_2__* links; } ;
struct TYPE_7__ {scalar_t__ enableLink; } ;
struct TYPE_8__ {TYPE_1__ conf; int /*<<< orphan*/ * hook; } ;

/* Variables and functions */
 int EINVAL ; 
 int EISCONN ; 
 int ENODEV ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  NG_HOOK_SET_RCVDATA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_PPP_HOOK_LINK_PREFIX ; 
 int NG_PPP_MAX_LINKS ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 TYPE_5__* ng_ppp_hook_names ; 
 int /*<<< orphan*/  ng_ppp_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strtoul (char const*,char**,int) ; 

__attribute__((used)) static int
ng_ppp_newhook(node_p node, hook_p hook, const char *name)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	hook_p *hookPtr = NULL;
	int linkNum = -1;
	int hookIndex = -1;

	/* Figure out which hook it is */
	if (strncmp(name, NG_PPP_HOOK_LINK_PREFIX,	/* a link hook? */
	    strlen(NG_PPP_HOOK_LINK_PREFIX)) == 0) {
		const char *cp;
		char *eptr;

		cp = name + strlen(NG_PPP_HOOK_LINK_PREFIX);
		if (!isdigit(*cp) || (cp[0] == '0' && cp[1] != '\0'))
			return (EINVAL);
		linkNum = (int)strtoul(cp, &eptr, 10);
		if (*eptr != '\0' || linkNum < 0 || linkNum >= NG_PPP_MAX_LINKS)
			return (EINVAL);
		hookPtr = &priv->links[linkNum].hook;
		hookIndex = ~linkNum;

		/* See if hook is already connected. */
		if (*hookPtr != NULL)
			return (EISCONN);

		/* Disallow more than one link unless multilink is enabled. */
		if (priv->links[linkNum].conf.enableLink &&
		    !priv->conf.enableMultilink && priv->numActiveLinks >= 1)
			return (ENODEV);

	} else {				/* must be a non-link hook */
		int i;

		for (i = 0; ng_ppp_hook_names[i].name != NULL; i++) {
			if (strcmp(name, ng_ppp_hook_names[i].name) == 0) {
				hookPtr = &priv->hooks[i];
				hookIndex = i;
				break;
			}
		}
		if (ng_ppp_hook_names[i].name == NULL)
			return (EINVAL);	/* no such hook */

		/* See if hook is already connected */
		if (*hookPtr != NULL)
			return (EISCONN);

		/* Every non-linkX hook have it's own function. */
		NG_HOOK_SET_RCVDATA(hook, ng_ppp_hook_names[i].fn);
	}

	/* OK */
	*hookPtr = hook;
	NG_HOOK_SET_PRIVATE(hook, (void *)(intptr_t)hookIndex);
	ng_ppp_update(node, 0);
	return (0);
}