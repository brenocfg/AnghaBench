#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xxx_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  void* hook_p ;
struct TYPE_6__ {int dlci; int /*<<< orphan*/ * hook; } ;
struct TYPE_5__ {int flags; void* debughook; TYPE_4__ downstream_hook; TYPE_4__* channel; } ;

/* Variables and functions */
 int EADDRINUSE ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (void*,TYPE_4__*) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_XXX_HOOK_DEBUG ; 
 int /*<<< orphan*/  NG_XXX_HOOK_DLCI_LEADIN ; 
 int /*<<< orphan*/  NG_XXX_HOOK_DOWNSTREAM ; 
 int SCF_RUNNING ; 
 int XXX_NUM_DLCIS ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int /*<<< orphan*/  ng_xxx_start_hardware (TYPE_1__* const) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strtoul (char const*,char**,int) ; 

__attribute__((used)) static int
ng_xxx_newhook(node_p node, hook_p hook, const char *name)
{
	const xxx_p xxxp = NG_NODE_PRIVATE(node);
	const char *cp;
	int dlci = 0;
	int chan;

#if 0
	/* Possibly start up the device if it's not already going */
	if ((xxxp->flags & SCF_RUNNING) == 0) {
		ng_xxx_start_hardware(xxxp);
	}
#endif

	/* Example of how one might use hooks with embedded numbers: All
	 * hooks start with 'dlci' and have a decimal trailing channel
	 * number up to 4 digits Use the leadin defined int he associated .h
	 * file. */
	if (strncmp(name,
	    NG_XXX_HOOK_DLCI_LEADIN, strlen(NG_XXX_HOOK_DLCI_LEADIN)) == 0) {
		char *eptr;

		cp = name + strlen(NG_XXX_HOOK_DLCI_LEADIN);
		if (!isdigit(*cp) || (cp[0] == '0' && cp[1] != '\0'))
			return (EINVAL);
		dlci = (int)strtoul(cp, &eptr, 10);
		if (*eptr != '\0' || dlci < 0 || dlci > 1023)
			return (EINVAL);

		/* We have a dlci, now either find it, or allocate it */
		for (chan = 0; chan < XXX_NUM_DLCIS; chan++)
			if (xxxp->channel[chan].dlci == dlci)
				break;
		if (chan == XXX_NUM_DLCIS) {
			for (chan = 0; chan < XXX_NUM_DLCIS; chan++)
				if (xxxp->channel[chan].dlci == -2)
					break;
			if (chan == XXX_NUM_DLCIS)
				return (ENOBUFS);
			xxxp->channel[chan].dlci = dlci;
		}
		if (xxxp->channel[chan].hook != NULL)
			return (EADDRINUSE);
		NG_HOOK_SET_PRIVATE(hook, xxxp->channel + chan);
		xxxp->channel[chan].hook = hook;
		return (0);
	} else if (strcmp(name, NG_XXX_HOOK_DOWNSTREAM) == 0) {
		/* Example of simple predefined hooks. */
		/* do something specific to the downstream connection */
		xxxp->downstream_hook.hook = hook;
		NG_HOOK_SET_PRIVATE(hook, &xxxp->downstream_hook);
	} else if (strcmp(name, NG_XXX_HOOK_DEBUG) == 0) {
		/* do something specific to a debug connection */
		xxxp->debughook = hook;
		NG_HOOK_SET_PRIVATE(hook, NULL);
	} else
		return (EINVAL);	/* not a hook we know about */
	return(0);
}