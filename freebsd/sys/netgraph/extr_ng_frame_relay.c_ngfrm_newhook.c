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
typedef  TYPE_1__* sc_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  void* hook_p ;
struct TYPE_6__ {int dlci; int /*<<< orphan*/ * hook; int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  datahooks; TYPE_4__* channel; TYPE_4__ downstream; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_ACTIVE ; 
 int EADDRINUSE ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  NG_FRAMERELAY_HOOK_DEBUG ; 
 int /*<<< orphan*/  NG_FRAMERELAY_HOOK_DLCI ; 
 int /*<<< orphan*/  NG_FRAMERELAY_HOOK_DOWNSTREAM ; 
 int /*<<< orphan*/  NG_HOOK_SET_PRIVATE (void*,TYPE_4__*) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int ngfrm_allocate_CTX (TYPE_1__* const,int) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strtoul (char const*,char**,int) ; 

__attribute__((used)) static int
ngfrm_newhook(node_p node, hook_p hook, const char *name)
{
	const sc_p sc = NG_NODE_PRIVATE(node);
	const char *cp;
	char *eptr;
	int dlci = 0;
	int ctxnum;

	/* Check if it's our friend the control hook */
	if (strcmp(name, NG_FRAMERELAY_HOOK_DEBUG) == 0) {
		NG_HOOK_SET_PRIVATE(hook, NULL);	/* paranoid */
		return (0);
	}

	/*
	 * All other hooks either start with 'dlci' and have a decimal
	 * trailing channel number up to 4 digits, or are the downstream
	 * hook.
	 */
	if (strncmp(name, NG_FRAMERELAY_HOOK_DLCI,
	    strlen(NG_FRAMERELAY_HOOK_DLCI)) != 0) {

		/* It must be the downstream connection */
		if (strcmp(name, NG_FRAMERELAY_HOOK_DOWNSTREAM) != 0)
			return EINVAL;

		/* Make sure we haven't already got one (paranoid) */
		if (sc->downstream.hook)
			return (EADDRINUSE);

		/* OK add it */
		NG_HOOK_SET_PRIVATE(hook, &sc->downstream);
		sc->downstream.hook = hook;
		sc->downstream.dlci = -1;
		sc->downstream.flags |= CHAN_ACTIVE;
		sc->datahooks++;
		return (0);
	}

	/* Must be a dlci hook at this point */
	cp = name + strlen(NG_FRAMERELAY_HOOK_DLCI);
	if (!isdigit(*cp) || (cp[0] == '0' && cp[1] != '\0'))
		return (EINVAL);
	dlci = (int)strtoul(cp, &eptr, 10);
	if (*eptr != '\0' || dlci < 0 || dlci > 1023)
		return (EINVAL);

	/*
	 * We have a dlci, now either find it, or allocate it. It's possible
	 * that we might have seen packets for it already and made an entry
	 * for it.
	 */
	ctxnum = ngfrm_allocate_CTX(sc, dlci);
	if (ctxnum == -1)
		return (ENOBUFS);

	/*
	 * Be paranoid: if it's got a hook already, that dlci is in use .
	 * Generic code can not catch all the synonyms (e.g. dlci016 vs
	 * dlci16)
	 */
	if (sc->channel[ctxnum].hook != NULL)
		return (EADDRINUSE);

	/*
	 * Put our hooks into it (pun not intended)
	 */
	sc->channel[ctxnum].flags |= CHAN_ACTIVE;
	NG_HOOK_SET_PRIVATE(hook, sc->channel + ctxnum);
	sc->channel[ctxnum].hook = hook;
	sc->datahooks++;
	return (0);
}