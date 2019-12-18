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
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/ * iffam_p ;
typedef  int /*<<< orphan*/ * hook_p ;
struct TYPE_4__ {int /*<<< orphan*/ * gif; } ;

/* Variables and functions */
 int EISCONN ; 
 int EPFNOSUPPORT ; 
 int /*<<< orphan*/  NG_GIF_DEMUX_HOOK_GIF ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** get_hook_from_iffam (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_iffam_from_name (char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static	int
ng_gif_demux_newhook(node_p node, hook_p hook, const char *name)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	iffam_p iffam;
	hook_p *hookptr;

	if (strcmp(NG_GIF_DEMUX_HOOK_GIF, name) == 0)
		hookptr = &priv->gif;
	else {
		iffam = get_iffam_from_name(name);
		if (iffam == NULL)
			return (EPFNOSUPPORT);
		hookptr = get_hook_from_iffam(NG_NODE_PRIVATE(node), iffam);
	}
	if (*hookptr != NULL)
		return (EISCONN);
	*hookptr = hook;
	return (0);
}