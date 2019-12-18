#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
typedef  TYPE_1__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/ * hook_p ;
struct TYPE_3__ {int lowerOrphan; int /*<<< orphan*/ * lower; } ;

/* Variables and functions */
 int EINVAL ; 
 int EISCONN ; 
 char* NG_GIF_HOOK_DIVERT ; 
 char* NG_GIF_HOOK_LOWER ; 
 char* NG_GIF_HOOK_ORPHAN ; 
 TYPE_1__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static	int
ng_gif_newhook(node_p node, hook_p hook, const char *name)
{
	const priv_p priv = NG_NODE_PRIVATE(node);
	u_char orphan = priv->lowerOrphan;
	hook_p *hookptr;

	/* Divert hook is an alias for lower */
	if (strcmp(name, NG_GIF_HOOK_DIVERT) == 0)
		name = NG_GIF_HOOK_LOWER;

	/* Which hook? */
	if (strcmp(name, NG_GIF_HOOK_LOWER) == 0) {
		hookptr = &priv->lower;
		orphan = 0;
	} else if (strcmp(name, NG_GIF_HOOK_ORPHAN) == 0) {
		hookptr = &priv->lower;
		orphan = 1;
	} else
		return (EINVAL);

	/* Check if already connected (shouldn't be, but doesn't hurt) */
	if (*hookptr != NULL)
		return (EISCONN);

	/* OK */
	*hookptr = hook;
	priv->lowerOrphan = orphan;
	return (0);
}