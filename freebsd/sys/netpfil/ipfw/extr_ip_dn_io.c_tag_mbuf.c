#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mbuf {int dummy; } ;
struct m_tag {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  info; } ;
struct ip_fw_args {int flags; int /*<<< orphan*/ * ifp; TYPE_1__ rule; } ;
struct dn_pkt_tag {int dn_dir; int /*<<< orphan*/  iphdr_off; int /*<<< orphan*/  output_time; int /*<<< orphan*/ * ifp; TYPE_1__ rule; } ;
struct TYPE_4__ {int /*<<< orphan*/  curr_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_HDR_LEN ; 
 int IPFW_ARGS_OUT ; 
 int /*<<< orphan*/  IPFW_ONEPASS ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PACKET_TAG_DUMMYNET ; 
 int PROTO_LAYER2 ; 
 TYPE_2__ dn_cfg ; 
 struct m_tag* m_tag_get (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  m_tag_prepend (struct mbuf*,struct m_tag*) ; 

__attribute__((used)) static inline int
tag_mbuf(struct mbuf *m, int dir, struct ip_fw_args *fwa)
{
	struct dn_pkt_tag *dt;
	struct m_tag *mtag;

	mtag = m_tag_get(PACKET_TAG_DUMMYNET,
		    sizeof(*dt), M_NOWAIT | M_ZERO);
	if (mtag == NULL)
		return 1;		/* Cannot allocate packet header. */
	m_tag_prepend(m, mtag);		/* Attach to mbuf chain. */
	dt = (struct dn_pkt_tag *)(mtag + 1);
	dt->rule = fwa->rule;
	dt->rule.info &= IPFW_ONEPASS;	/* only keep this info */
	dt->dn_dir = dir;
	dt->ifp = fwa->flags & IPFW_ARGS_OUT ? fwa->ifp : NULL;
	/* dt->output tame is updated as we move through */
	dt->output_time = dn_cfg.curr_time;
	dt->iphdr_off = (dir & PROTO_LAYER2) ? ETHER_HDR_LEN : 0;
	return 0;
}