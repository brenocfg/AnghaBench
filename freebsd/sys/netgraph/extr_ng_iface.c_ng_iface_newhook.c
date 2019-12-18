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
typedef  int /*<<< orphan*/  priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/ * iffam_p ;
typedef  int /*<<< orphan*/ * hook_p ;

/* Variables and functions */
 int EISCONN ; 
 int EPFNOSUPPORT ; 
 int /*<<< orphan*/  NG_HOOK_HI_STACK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_HOOK_SET_TO_INBOUND (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRIV_WLOCK (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  PRIV_WUNLOCK (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ ** get_hook_from_iffam (int /*<<< orphan*/  const,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * get_iffam_from_name (char const*) ; 

__attribute__((used)) static int
ng_iface_newhook(node_p node, hook_p hook, const char *name)
{
	const iffam_p iffam = get_iffam_from_name(name);
	const priv_p priv = NG_NODE_PRIVATE(node);
	hook_p *hookptr;

	if (iffam == NULL)
		return (EPFNOSUPPORT);
	PRIV_WLOCK(priv);
	hookptr = get_hook_from_iffam(priv, iffam);
	if (*hookptr != NULL) {
		PRIV_WUNLOCK(priv);
		return (EISCONN);
	}
	*hookptr = hook;
	NG_HOOK_HI_STACK(hook);
	NG_HOOK_SET_TO_INBOUND(hook);
	PRIV_WUNLOCK(priv);
	return (0);
}