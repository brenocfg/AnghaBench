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
typedef  int /*<<< orphan*/  uint16_t ;
struct mbuf {int dummy; } ;
typedef  TYPE_2__* priv_p ;
typedef  int /*<<< orphan*/  node_p ;
typedef  struct mbuf* item_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_4__ {int enableCompression; } ;
struct TYPE_5__ {TYPE_1__ conf; } ;
typedef  struct mbuf* NGI_M ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  NGI_GET_M (struct mbuf*,struct mbuf*) ; 
 int /*<<< orphan*/  NG_FREE_ITEM (struct mbuf*) ; 
 int /*<<< orphan*/  NG_HOOK_NODE (int /*<<< orphan*/ ) ; 
 TYPE_2__* NG_NODE_PRIVATE (int /*<<< orphan*/  const) ; 
#define  NG_PPP_COMPRESS_FULL 129 
#define  NG_PPP_COMPRESS_NONE 128 
 int /*<<< orphan*/  PROT_COMPD ; 
 int /*<<< orphan*/  PROT_VALID (int /*<<< orphan*/ ) ; 
 int ng_ppp_crypt_xmit (int /*<<< orphan*/  const,struct mbuf*,int /*<<< orphan*/ ) ; 
 struct mbuf* ng_ppp_cutproto (struct mbuf*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ng_ppp_rcvdata_compress(hook_p hook, item_p item)
{
	const node_p node = NG_HOOK_NODE(hook);
	const priv_p priv = NG_NODE_PRIVATE(node);
	uint16_t proto;

	switch (priv->conf.enableCompression) {
	    case NG_PPP_COMPRESS_NONE:
		NG_FREE_ITEM(item);
		return (ENXIO);
	    case NG_PPP_COMPRESS_FULL:
		{
			struct mbuf *m;

			NGI_GET_M(item, m);
			if ((m = ng_ppp_cutproto(m, &proto)) == NULL) {
				NG_FREE_ITEM(item);
				return (EIO);
			}
			NGI_M(item) = m;
			if (!PROT_VALID(proto)) {
				NG_FREE_ITEM(item);
				return (EIO);
			}
		}
		break;
	    default:
		proto = PROT_COMPD;
		break;
	}
	return (ng_ppp_crypt_xmit(node, item, proto));
}