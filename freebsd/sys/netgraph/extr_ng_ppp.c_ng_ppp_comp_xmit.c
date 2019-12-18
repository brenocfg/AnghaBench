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
typedef  int uint16_t ;
struct mbuf {int dummy; } ;
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  item_p ;
struct TYPE_4__ {scalar_t__ enableCompression; } ;
struct TYPE_5__ {int /*<<< orphan*/ ** hooks; TYPE_1__ conf; } ;
typedef  struct mbuf* NGI_M ;

/* Variables and functions */
 int ENOBUFS ; 
 size_t HOOK_INDEX_COMPRESS ; 
 int /*<<< orphan*/  NGI_GET_M (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_FWD_ITEM_HOOK (int,struct mbuf*,int /*<<< orphan*/ *) ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int PROT_COMPD ; 
 int PROT_CRYPTD ; 
 struct mbuf* ng_ppp_addproto (struct mbuf*,int,int /*<<< orphan*/ ) ; 
 int ng_ppp_crypt_xmit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ng_ppp_comp_xmit(node_p node, item_p item, uint16_t proto)
{
	const priv_p priv = NG_NODE_PRIVATE(node);

	if (priv->conf.enableCompression &&
	    proto < 0x4000 &&
	    proto != PROT_COMPD &&
	    proto != PROT_CRYPTD &&
	    priv->hooks[HOOK_INDEX_COMPRESS] != NULL) {
		struct mbuf *m;
		int error;

		NGI_GET_M(item, m);
		if ((m = ng_ppp_addproto(m, proto, 0)) == NULL) {
			NG_FREE_ITEM(item);
			return (ENOBUFS);
		}
		NGI_M(item) = m;

		/* Send packet out hook. */
		NG_FWD_ITEM_HOOK(error, item, priv->hooks[HOOK_INDEX_COMPRESS]);
		return (error);
	}

	return (ng_ppp_crypt_xmit(node, item, proto));
}