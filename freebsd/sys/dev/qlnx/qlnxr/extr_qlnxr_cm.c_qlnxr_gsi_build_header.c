#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
union ib_gid {int /*<<< orphan*/ * raw; } ;
typedef  int /*<<< orphan*/ * u8 ;
typedef  void* u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct qlnxr_qp {int /*<<< orphan*/  sq_psn; } ;
struct qlnxr_dev {TYPE_12__* ha; union ib_gid* sgid_tbl; } ;
struct TYPE_19__ {void* source_qpn; void* qkey; } ;
struct TYPE_18__ {int solicited_event; int /*<<< orphan*/  opcode; void* psn; void* destination_qpn; int /*<<< orphan*/  pkey; } ;
struct TYPE_17__ {void* daddr; void* saddr; int /*<<< orphan*/  ttl; void* frag_off; int /*<<< orphan*/  tos; int /*<<< orphan*/  protocol; } ;
struct TYPE_24__ {int /*<<< orphan*/ * raw; } ;
struct TYPE_23__ {int /*<<< orphan*/ * raw; } ;
struct TYPE_25__ {int next_header; TYPE_8__ source_gid; TYPE_7__ destination_gid; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  traffic_class; } ;
struct TYPE_22__ {int /*<<< orphan*/ ** smac_h; int /*<<< orphan*/ ** dmac_h; void* type; } ;
struct TYPE_21__ {void* type; void* tag; } ;
struct ib_ud_header {TYPE_3__ deth; TYPE_2__ bth; TYPE_1__ ip4; TYPE_9__ grh; TYPE_6__ eth; TYPE_5__ vlan; } ;
struct ib_send_wr {int num_sge; int send_flags; int /*<<< orphan*/  wr_id; int /*<<< orphan*/  opcode; TYPE_4__* sg_list; } ;
struct ib_global_route {size_t sgid_index; TYPE_7__ dgid; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  traffic_class; } ;
struct ib_ah_attr {int /*<<< orphan*/ ** dmac; struct ib_global_route grh; } ;
struct TYPE_20__ {scalar_t__ length; } ;
struct TYPE_16__ {int /*<<< orphan*/ ** primary_mac; } ;
struct TYPE_15__ {struct ib_ah_attr attr; } ;
struct TYPE_14__ {int remote_qpn; int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  ETH_P_ROCE ; 
 int /*<<< orphan*/  IB_OPCODE_UD_SEND_ONLY ; 
 int IB_SEND_SOLICITED ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  IP_DF ; 
 void* OSAL_CPU_TO_BE32 (int) ; 
 int QLNXR_GSI_QPN ; 
 size_t QLNXR_MAX_SGID ; 
 int /*<<< orphan*/  QLNXR_ROCE_PKEY_DEFAULT ; 
 int /*<<< orphan*/  QL_DPRINT11 (TYPE_12__*,char*) ; 
 int /*<<< orphan*/  QL_DPRINT12 (TYPE_12__*,char*,...) ; 
 int ROCE_V1 ; 
 TYPE_11__* get_qlnxr_ah (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int ib_ud_header_init (int,int,int,int,int,int,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 void* qedr_get_ipv4_from_gid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlnxr_get_dmac (struct qlnxr_dev*,struct ib_ah_attr*,int /*<<< orphan*/ **) ; 
 int qlnxr_get_vlan_id_gsi (struct ib_ah_attr*,int /*<<< orphan*/ *) ; 
 TYPE_10__* ud_wr (struct ib_send_wr*) ; 

__attribute__((used)) static inline int
qlnxr_gsi_build_header(struct qlnxr_dev *dev,
		struct qlnxr_qp *qp,
		struct ib_send_wr *swr,
		struct ib_ud_header *udh,
		int *roce_mode)
{
	bool has_vlan = false, has_grh_ipv6 = true;
	struct ib_ah_attr *ah_attr = &get_qlnxr_ah((ud_wr(swr)->ah))->attr;
	struct ib_global_route *grh = &ah_attr->grh;
	union ib_gid sgid;
	int send_size = 0;
	u16 vlan_id = 0;
	u16 ether_type;

#if __FreeBSD_version >= 1102000
	int rc = 0;
	int ip_ver = 0;
	bool has_udp = false;
#endif /* #if __FreeBSD_version >= 1102000 */


#if !DEFINE_IB_AH_ATTR_WITH_DMAC
	u8 mac[ETH_ALEN];
#endif
	int i;

	send_size = 0;
	for (i = 0; i < swr->num_sge; ++i)
		send_size += swr->sg_list[i].length;

	has_vlan = qlnxr_get_vlan_id_gsi(ah_attr, &vlan_id);
	ether_type = ETH_P_ROCE;
	*roce_mode = ROCE_V1;
	if (grh->sgid_index < QLNXR_MAX_SGID)
		sgid = dev->sgid_tbl[grh->sgid_index];
	else
		sgid = dev->sgid_tbl[0];

#if __FreeBSD_version >= 1102000

	rc = ib_ud_header_init(send_size, false /* LRH */, true /* ETH */,
			has_vlan, has_grh_ipv6, ip_ver, has_udp,
			0 /* immediate */, udh);

	if (rc) {
		QL_DPRINT11(dev->ha, "gsi post send: failed to init header\n");
		return rc;
	}

#else
	ib_ud_header_init(send_size, false /* LRH */, true /* ETH */,
			  has_vlan, has_grh_ipv6, 0 /* immediate */, udh);

#endif /* #if __FreeBSD_version >= 1102000 */

	/* ENET + VLAN headers*/
#if DEFINE_IB_AH_ATTR_WITH_DMAC
	memcpy(udh->eth.dmac_h, ah_attr->dmac, ETH_ALEN);
#else
	qlnxr_get_dmac(dev, ah_attr, mac);
	memcpy(udh->eth.dmac_h, mac, ETH_ALEN);
#endif
	memcpy(udh->eth.smac_h, dev->ha->primary_mac, ETH_ALEN);
	if (has_vlan) {
		udh->eth.type = htons(ETH_P_8021Q);
		udh->vlan.tag = htons(vlan_id);
		udh->vlan.type = htons(ether_type);
	} else {
		udh->eth.type = htons(ether_type);
	}

	for (int j = 0; j < 4; j++) {
		QL_DPRINT12(dev->ha, "destination mac: %x\n",
				udh->eth.dmac_h[j]);
	}
	for (int j = 0; j < 4; j++) {
		QL_DPRINT12(dev->ha, "source mac: %x\n",
				udh->eth.smac_h[j]);
	}
	
	QL_DPRINT12(dev->ha, "QP: %p, opcode: %d, wq: %lx, roce: %x, hops:%d,"
			"imm : %d, vlan :%d, AH: %p\n",
			qp, swr->opcode, swr->wr_id, *roce_mode, grh->hop_limit,
			0, has_vlan, get_qlnxr_ah((ud_wr(swr)->ah)));

	if (has_grh_ipv6) {
		/* GRH / IPv6 header */
		udh->grh.traffic_class = grh->traffic_class;
		udh->grh.flow_label = grh->flow_label;
		udh->grh.hop_limit = grh->hop_limit;
		udh->grh.destination_gid = grh->dgid;
		memcpy(&udh->grh.source_gid.raw, &sgid.raw,
		       sizeof(udh->grh.source_gid.raw));
		QL_DPRINT12(dev->ha, "header: tc: %x, flow_label : %x, "
			"hop_limit: %x \n", udh->grh.traffic_class,
			udh->grh.flow_label, udh->grh.hop_limit);
		for (i = 0; i < 16; i++) {
			QL_DPRINT12(dev->ha, "udh dgid = %x\n", udh->grh.destination_gid.raw[i]);
		}
		for (i = 0; i < 16; i++) {
			QL_DPRINT12(dev->ha, "udh sgid = %x\n", udh->grh.source_gid.raw[i]);
		}
		udh->grh.next_header = 0x1b;
	}
#ifdef DEFINE_IB_UD_HEADER_INIT_UDP_PRESENT 
        /* This is for RoCEv2 */
	else {
                /* IPv4 header */
                u32 ipv4_addr;

                udh->ip4.protocol = IPPROTO_UDP;
                udh->ip4.tos = htonl(grh->flow_label);
                udh->ip4.frag_off = htons(IP_DF);
                udh->ip4.ttl = grh->hop_limit;

                ipv4_addr = qedr_get_ipv4_from_gid(sgid.raw);
                udh->ip4.saddr = ipv4_addr;
                ipv4_addr = qedr_get_ipv4_from_gid(grh->dgid.raw);
                udh->ip4.daddr = ipv4_addr;
                /* note: checksum is calculated by the device */
        }
#endif

	/* BTH */
	udh->bth.solicited_event = !!(swr->send_flags & IB_SEND_SOLICITED);
	udh->bth.pkey = QLNXR_ROCE_PKEY_DEFAULT;/* TODO: ib_get_cahced_pkey?! */
	//udh->bth.destination_qpn = htonl(ud_wr(swr)->remote_qpn);
	udh->bth.destination_qpn = OSAL_CPU_TO_BE32(ud_wr(swr)->remote_qpn);
	//udh->bth.psn = htonl((qp->sq_psn++) & ((1 << 24) - 1));
	udh->bth.psn = OSAL_CPU_TO_BE32((qp->sq_psn++) & ((1 << 24) - 1));
	udh->bth.opcode = IB_OPCODE_UD_SEND_ONLY;

	/* DETH */
	//udh->deth.qkey = htonl(0x80010000); /* qp->qkey */ /* TODO: what is?! */
	//udh->deth.source_qpn = htonl(QLNXR_GSI_QPN);
	udh->deth.qkey = OSAL_CPU_TO_BE32(0x80010000); /* qp->qkey */ /* TODO: what is?! */
	udh->deth.source_qpn = OSAL_CPU_TO_BE32(QLNXR_GSI_QPN);
	QL_DPRINT12(dev->ha, "exit\n");
	return 0;
}