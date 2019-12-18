#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
struct TYPE_4__ {scalar_t__ enableDecryption; } ;
struct TYPE_5__ {int /*<<< orphan*/ ** hooks; TYPE_1__ conf; } ;

/* Variables and functions */
 size_t HOOK_INDEX_DECRYPT ; 
 int /*<<< orphan*/  NG_FWD_ITEM_HOOK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ PROT_CRYPTD ; 
 int ng_ppp_bypass (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int ng_ppp_comp_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
ng_ppp_crypt_recv(node_p node, item_p item, uint16_t proto, uint16_t linkNum)
{
	const priv_p priv = NG_NODE_PRIVATE(node);

	if (proto == PROT_CRYPTD) {
		if (priv->conf.enableDecryption &&
		    priv->hooks[HOOK_INDEX_DECRYPT] != NULL) {
			int error;

			/* Send packet out hook. */
			NG_FWD_ITEM_HOOK(error, item,
			    priv->hooks[HOOK_INDEX_DECRYPT]);
			return (error);
		} else {
			/* Disabled protos MUST be silently discarded, but
			 * unsupported MUST not. Let user-level decide this. */
			return (ng_ppp_bypass(node, item, proto, linkNum));
		}
	}

	return (ng_ppp_comp_recv(node, item, proto, linkNum));
}