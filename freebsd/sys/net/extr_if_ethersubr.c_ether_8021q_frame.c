#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int len; int /*<<< orphan*/  ether_vtag; } ;
struct mbuf {int /*<<< orphan*/  m_flags; TYPE_1__ m_pkthdr; } ;
struct m_tag {int dummy; } ;
struct ifnet {scalar_t__ if_type; int if_capenable; } ;
typedef  int /*<<< orphan*/  pad ;

/* Variables and functions */
 int ETHERMIN ; 
 int ETHER_HDR_LEN ; 
 int /*<<< orphan*/  EVL_MAKETAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFCAP_VLAN_HWTAGGING ; 
 scalar_t__ IFT_ETHER ; 
 int /*<<< orphan*/  MTAG_8021Q ; 
 int /*<<< orphan*/  MTAG_8021Q_PCP_OUT ; 
 int /*<<< orphan*/  M_VLANTAG ; 
 scalar_t__ V_soft_pad ; 
 struct mbuf* ether_vlanencap (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 
 int /*<<< orphan*/  m_append (struct mbuf*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct m_tag* m_tag_locate (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  min (int,int) ; 
 scalar_t__ vlan_mtag_pcp ; 

bool
ether_8021q_frame(struct mbuf **mp, struct ifnet *ife, struct ifnet *p,
    uint16_t vid, uint8_t pcp)
{
	struct m_tag *mtag;
	int n;
	uint16_t tag;
	static const char pad[8];	/* just zeros */

	/*
	 * Pad the frame to the minimum size allowed if told to.
	 * This option is in accord with IEEE Std 802.1Q, 2003 Ed.,
	 * paragraph C.4.4.3.b.  It can help to work around buggy
	 * bridges that violate paragraph C.4.4.3.a from the same
	 * document, i.e., fail to pad short frames after untagging.
	 * E.g., a tagged frame 66 bytes long (incl. FCS) is OK, but
	 * untagging it will produce a 62-byte frame, which is a runt
	 * and requires padding.  There are VLAN-enabled network
	 * devices that just discard such runts instead or mishandle
	 * them somehow.
	 */
	if (V_soft_pad && p->if_type == IFT_ETHER) {
		for (n = ETHERMIN + ETHER_HDR_LEN - (*mp)->m_pkthdr.len;
		     n > 0; n -= sizeof(pad)) {
			if (!m_append(*mp, min(n, sizeof(pad)), pad))
				break;
		}
		if (n > 0) {
			m_freem(*mp);
			*mp = NULL;
			if_printf(ife, "cannot pad short frame");
			return (false);
		}
	}

	/*
	 * If underlying interface can do VLAN tag insertion itself,
	 * just pass the packet along. However, we need some way to
	 * tell the interface where the packet came from so that it
	 * knows how to find the VLAN tag to use, so we attach a
	 * packet tag that holds it.
	 */
	if (vlan_mtag_pcp && (mtag = m_tag_locate(*mp, MTAG_8021Q,
	    MTAG_8021Q_PCP_OUT, NULL)) != NULL)
		tag = EVL_MAKETAG(vid, *(uint8_t *)(mtag + 1), 0);
	else
		tag = EVL_MAKETAG(vid, pcp, 0);
	if (p->if_capenable & IFCAP_VLAN_HWTAGGING) {
		(*mp)->m_pkthdr.ether_vtag = tag;
		(*mp)->m_flags |= M_VLANTAG;
	} else {
		*mp = ether_vlanencap(*mp, tag);
		if (*mp == NULL) {
			if_printf(ife, "unable to prepend 802.1Q header");
			return (false);
		}
	}
	return (true);
}