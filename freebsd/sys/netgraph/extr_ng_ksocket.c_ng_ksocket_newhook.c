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
struct thread {int /*<<< orphan*/  td_ucred; } ;
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/ * hook_p ;
struct TYPE_4__ {int flags; int /*<<< orphan*/ * hook; int /*<<< orphan*/  so; } ;

/* Variables and functions */
 int EINVAL ; 
 int EISCONN ; 
 int KSF_CLONED ; 
 int KSF_EMBRYONIC ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_1__* const,int /*<<< orphan*/ ) ; 
 int NG_HOOKSIZ ; 
 int /*<<< orphan*/  NG_HOOK_FORCE_QUEUE (int /*<<< orphan*/ *) ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  ng_ksocket_families ; 
 int ng_ksocket_parse (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ng_ksocket_protos ; 
 int /*<<< orphan*/  ng_ksocket_types ; 
 int /*<<< orphan*/  siblings ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int socreate (int,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,struct thread*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int
ng_ksocket_newhook(node_p node, hook_p hook, const char *name0)
{
	struct thread *td = curthread;	/* XXX broken */
	const priv_p priv = NG_NODE_PRIVATE(node);
	char *s1, *s2, name[NG_HOOKSIZ];
	int family, type, protocol, error;

	/* Check if we're already connected */
	if (priv->hook != NULL)
		return (EISCONN);

	if (priv->flags & KSF_CLONED) {
		if (priv->flags & KSF_EMBRYONIC) {
			/* Remove ourselves from our parent's embryo list */
			LIST_REMOVE(priv, siblings);
			priv->flags &= ~KSF_EMBRYONIC;
		}
	} else {
		/* Extract family, type, and protocol from hook name */
		snprintf(name, sizeof(name), "%s", name0);
		s1 = name;
		if ((s2 = strchr(s1, '/')) == NULL)
			return (EINVAL);
		*s2++ = '\0';
		family = ng_ksocket_parse(ng_ksocket_families, s1, 0);
		if (family == -1)
			return (EINVAL);
		s1 = s2;
		if ((s2 = strchr(s1, '/')) == NULL)
			return (EINVAL);
		*s2++ = '\0';
		type = ng_ksocket_parse(ng_ksocket_types, s1, 0);
		if (type == -1)
			return (EINVAL);
		s1 = s2;
		protocol = ng_ksocket_parse(ng_ksocket_protos, s1, family);
		if (protocol == -1)
			return (EINVAL);

		/* Create the socket */
		error = socreate(family, &priv->so, type, protocol,
		   td->td_ucred, td);
		if (error != 0)
			return (error);

		/* XXX call soreserve() ? */

	}

	/* OK */
	priv->hook = hook;

	/*
	 * In case of misconfigured routing a packet may reenter
	 * ksocket node recursively. Decouple stack to avoid possible
	 * panics about sleeping with locks held.
	 */
	NG_HOOK_FORCE_QUEUE(hook);

	return(0);
}