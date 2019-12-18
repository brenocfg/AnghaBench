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
struct ng_atmllc_priv {int /*<<< orphan*/ * fddi; int /*<<< orphan*/ * ether; int /*<<< orphan*/ * atm; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  void* hook_p ;

/* Variables and functions */
 int EINVAL ; 
 int EISCONN ; 
 int /*<<< orphan*/  NG_ATMLLC_HOOK_ATM ; 
 int /*<<< orphan*/  NG_ATMLLC_HOOK_ETHER ; 
 int /*<<< orphan*/  NG_ATMLLC_HOOK_FDDI ; 
 struct ng_atmllc_priv* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_atmllc_newhook(node_p node, hook_p hook, const char *name)
{
	struct	ng_atmllc_priv *priv;

	priv = NG_NODE_PRIVATE(node);

	if (strcmp(name, NG_ATMLLC_HOOK_ATM) == 0) {
		if (priv->atm != NULL) {
			return (EISCONN);
		}
		priv->atm = hook;
	} else if (strcmp(name, NG_ATMLLC_HOOK_ETHER) == 0) {
		if (priv->ether != NULL) {
			return (EISCONN);
		}
		priv->ether = hook;
	} else if (strcmp(name, NG_ATMLLC_HOOK_FDDI) == 0) {
		if (priv->fddi != NULL) {
			return (EISCONN);
		}
		priv->fddi = hook;
	} else {
		return (EINVAL);
	}

	return (0);
}