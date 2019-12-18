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
struct TYPE_4__ {scalar_t__ enableDecompression; } ;
struct TYPE_5__ {int /*<<< orphan*/ ** hooks; TYPE_1__ conf; } ;
typedef  struct mbuf* NGI_M ;

/* Variables and functions */
 int EIO ; 
 size_t HOOK_INDEX_DECOMPRESS ; 
 int /*<<< orphan*/  NGI_GET_M (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  NG_FREE_ITEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_FWD_ITEM_HOOK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 scalar_t__ NG_PPP_DECOMPRESS_FULL ; 
 int PROT_COMPD ; 
 struct mbuf* ng_ppp_addproto (struct mbuf*,int,int /*<<< orphan*/ ) ; 
 int ng_ppp_bypass (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int ng_ppp_hcomp_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
ng_ppp_comp_recv(node_p node, item_p item, uint16_t proto, uint16_t linkNum)
{
	const priv_p priv = NG_NODE_PRIVATE(node);

	if (proto < 0x4000 &&
	    ((proto == PROT_COMPD && priv->conf.enableDecompression) ||
	    priv->conf.enableDecompression == NG_PPP_DECOMPRESS_FULL) &&
	    priv->hooks[HOOK_INDEX_DECOMPRESS] != NULL) {
		int error;

		if (priv->conf.enableDecompression == NG_PPP_DECOMPRESS_FULL) {
			struct mbuf *m;
			NGI_GET_M(item, m);
			if ((m = ng_ppp_addproto(m, proto, 0)) == NULL) {
				NG_FREE_ITEM(item);
				return (EIO);
			}
			NGI_M(item) = m;
		}

		/* Send packet out hook. */
		NG_FWD_ITEM_HOOK(error, item,
		    priv->hooks[HOOK_INDEX_DECOMPRESS]);
		return (error);
	} else if (proto == PROT_COMPD) {
		/* Disabled protos MUST be silently discarded, but
		 * unsupported MUST not. Let user-level decide this. */
		return (ng_ppp_bypass(node, item, proto, linkNum));
	}

	return (ng_ppp_hcomp_recv(node, item, proto, linkNum));
}