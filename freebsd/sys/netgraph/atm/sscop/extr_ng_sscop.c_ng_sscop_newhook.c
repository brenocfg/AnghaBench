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
struct priv {void* manage; void* lower; void* upper; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  void* hook_p ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NG_HOOK_SET_RCVDATA (void*,int /*<<< orphan*/ ) ; 
 struct priv* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_sscop_rcvmanage ; 
 int /*<<< orphan*/  ng_sscop_rcvupper ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
ng_sscop_newhook(node_p node, hook_p hook, const char *name)
{
	struct priv *priv = NG_NODE_PRIVATE(node);

	if(strcmp(name, "upper") == 0) {
		priv->upper = hook;
		NG_HOOK_SET_RCVDATA(hook, ng_sscop_rcvupper);
	} else if(strcmp(name, "lower") == 0) {
		priv->lower = hook;
	} else if(strcmp(name, "manage") == 0) {
		priv->manage = hook;
		NG_HOOK_SET_RCVDATA(hook, ng_sscop_rcvmanage);
	} else
		return EINVAL;

	return 0;
}