#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_47__   TYPE_9__ ;
typedef  struct TYPE_46__   TYPE_8__ ;
typedef  struct TYPE_45__   TYPE_7__ ;
typedef  struct TYPE_44__   TYPE_6__ ;
typedef  struct TYPE_43__   TYPE_5__ ;
typedef  struct TYPE_42__   TYPE_4__ ;
typedef  struct TYPE_41__   TYPE_3__ ;
typedef  struct TYPE_40__   TYPE_2__ ;
typedef  struct TYPE_39__   TYPE_23__ ;
typedef  struct TYPE_38__   TYPE_21__ ;
typedef  struct TYPE_37__   TYPE_20__ ;
typedef  struct TYPE_36__   TYPE_1__ ;
typedef  struct TYPE_35__   TYPE_19__ ;
typedef  struct TYPE_34__   TYPE_18__ ;
typedef  struct TYPE_33__   TYPE_17__ ;
typedef  struct TYPE_32__   TYPE_16__ ;
typedef  struct TYPE_31__   TYPE_15__ ;
typedef  struct TYPE_30__   TYPE_14__ ;
typedef  struct TYPE_29__   TYPE_13__ ;
typedef  struct TYPE_28__   TYPE_12__ ;
typedef  struct TYPE_27__   TYPE_11__ ;
typedef  struct TYPE_26__   TYPE_10__ ;

/* Type definitions */
struct TYPE_40__ {int /*<<< orphan*/  interface_id; int /*<<< orphan*/  subnet_prefix; } ;
union ib_gid {struct mlx4_wqe_inline_seg* raw; TYPE_2__ global; } ;
typedef  int u16 ;
struct mlx4_wqe_mlx_seg {int flags; void* sched_prio; void* rlid; } ;
struct mlx4_wqe_inline_seg {int byte_count; } ;
struct mlx4_wqe_ctrl_seg {struct mlx4_wqe_inline_seg imm; struct mlx4_wqe_inline_seg* srcrb_flags16; } ;
struct TYPE_34__ {int qkey; int source_qpn; } ;
struct TYPE_33__ {int solicited_event; int destination_qpn; int psn; void* pkey; int /*<<< orphan*/  opcode; } ;
struct TYPE_31__ {int service_level; int virtual_lane; void* source_lid; void* destination_lid; } ;
struct TYPE_30__ {void* tag; void* type; } ;
struct TYPE_29__ {void* type; struct mlx4_wqe_inline_seg* dmac_h; union ib_gid* smac_h; } ;
struct TYPE_46__ {scalar_t__ csum; void* sport; void* dport; } ;
struct TYPE_45__ {int tos; int /*<<< orphan*/  check; struct mlx4_wqe_inline_seg daddr; struct mlx4_wqe_inline_seg saddr; int /*<<< orphan*/  ttl; void* frag_off; scalar_t__ id; } ;
struct TYPE_43__ {struct mlx4_wqe_inline_seg* raw; } ;
struct TYPE_44__ {int traffic_class; int flow_label; TYPE_5__ destination_gid; union ib_gid source_gid; int /*<<< orphan*/  hop_limit; } ;
struct TYPE_39__ {int immediate_present; TYPE_18__ deth; TYPE_17__ bth; TYPE_15__ lrh; TYPE_14__ vlan; TYPE_13__ eth; int /*<<< orphan*/  immediate_data; TYPE_8__ udp; TYPE_7__ ip4; TYPE_6__ grh; } ;
struct TYPE_35__ {unsigned int qp_num; struct ib_device* device; } ;
struct TYPE_37__ {int port; TYPE_19__ ibqp; } ;
struct mlx4_ib_sqp {unsigned int qkey; struct mlx4_wqe_inline_seg* header_buf; TYPE_23__ ud_header; TYPE_20__ qp; int /*<<< orphan*/  send_psn; int /*<<< orphan*/  pkey_index; } ;
struct TYPE_27__ {void* vlan; struct mlx4_wqe_inline_seg* mac; int /*<<< orphan*/  s_mac; int /*<<< orphan*/  hop_limit; } ;
struct TYPE_26__ {int port_pd; size_t gid_index; int sl_tclass_flowlabel; int g_slid; struct mlx4_wqe_inline_seg* dgid; int /*<<< orphan*/  hop_limit; void* dlid; } ;
struct TYPE_28__ {TYPE_11__ eth; TYPE_10__ ib; } ;
struct mlx4_ib_ah {TYPE_12__ av; } ;
struct in6_addr {int byte_count; } ;
struct TYPE_47__ {int /*<<< orphan*/  imm_data; } ;
struct TYPE_32__ {int num_sge; int opcode; int send_flags; TYPE_9__ ex; TYPE_1__* sg_list; } ;
struct ib_ud_wr {unsigned int remote_qpn; int remote_qkey; int /*<<< orphan*/  pkey_index; TYPE_16__ wr; int /*<<< orphan*/  ah; } ;
struct ib_gid_attr {scalar_t__ gid_type; scalar_t__ ndev; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  sgid ;
typedef  int /*<<< orphan*/  in6 ;
typedef  int __be32 ;
struct TYPE_42__ {TYPE_3__* demux; } ;
struct TYPE_41__ {int /*<<< orphan*/ * guid_cache; int /*<<< orphan*/  subnet_prefix; } ;
struct TYPE_38__ {TYPE_4__ sriov; int /*<<< orphan*/  dev; } ;
struct TYPE_36__ {scalar_t__ length; } ;

/* Variables and functions */
 unsigned int ALIGN (int,int) ; 
 int EINVAL ; 
 int ENOENT ; 
 int ETHERTYPE_IP ; 
 int ETHERTYPE_IPV6 ; 
 scalar_t__ IB_GID_TYPE_ROCE_UDP_ENCAP ; 
 void* IB_LID_PERMISSIVE ; 
 scalar_t__ IB_LINK_LAYER_ETHERNET ; 
 int /*<<< orphan*/  IB_OPCODE_UD_SEND_ONLY ; 
 int /*<<< orphan*/  IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE ; 
 int IB_SEND_SOLICITED ; 
#define  IB_WR_SEND 129 
#define  IB_WR_SEND_WITH_IMM 128 
 int /*<<< orphan*/  IP_DF ; 
 int MLX4_IB_IBOE_ETHERTYPE ; 
 int MLX4_INLINE_ALIGN ; 
 int /*<<< orphan*/  MLX4_ROCEV2_QP1_SPORT ; 
 unsigned int MLX4_WQE_CTRL_CQ_UPDATE ; 
 unsigned int MLX4_WQE_CTRL_FORCE_LOOPBACK ; 
 int MLX4_WQE_MLX_SLR ; 
 int MLX4_WQE_MLX_VL15 ; 
 int /*<<< orphan*/  ROCE_V2_UDP_DPORT ; 
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 
 int be16_to_cpu (void*) ; 
 int be32_to_cpu (int) ; 
 void* cpu_to_be16 (int) ; 
 int cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (scalar_t__) ; 
 int /*<<< orphan*/  ether_addr_copy (union ib_gid*,int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int ib_get_cached_gid (struct ib_device*,int,size_t,union ib_gid*,struct ib_gid_attr*) ; 
 int /*<<< orphan*/  ib_get_cached_pkey (struct ib_device*,int,int /*<<< orphan*/ ,int*) ; 
 int ib_ud_header_init (int,int,int,int,int,int,int,int /*<<< orphan*/ ,TYPE_23__*) ; 
 int ib_ud_header_pack (TYPE_23__*,struct mlx4_wqe_inline_seg*) ; 
 int /*<<< orphan*/  ib_ud_ip4_csum (TYPE_23__*) ; 
 scalar_t__ ipv6_addr_v4mapped (struct mlx4_wqe_inline_seg*) ; 
 int /*<<< orphan*/  memcmp (union ib_gid*,struct mlx4_wqe_inline_seg*,int) ; 
 int /*<<< orphan*/  memcpy (struct mlx4_wqe_inline_seg*,struct mlx4_wqe_inline_seg*,int) ; 
 int mlx4_get_roce_gid_from_slave (int /*<<< orphan*/ ,int,size_t,struct mlx4_wqe_inline_seg*) ; 
 int mlx4_ib_ah_grh_present (struct mlx4_ib_ah*) ; 
 scalar_t__ mlx4_is_mfunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 scalar_t__ rdma_port_get_link_layer (struct ib_device*,int) ; 
 int sl_to_vl (TYPE_21__*,int,int) ; 
 struct mlx4_ib_ah* to_mah (int /*<<< orphan*/ ) ; 
 TYPE_21__* to_mdev (struct ib_device*) ; 
 int /*<<< orphan*/  wmb () ; 
 struct mlx4_wqe_inline_seg zgid ; 

__attribute__((used)) static int build_mlx_header(struct mlx4_ib_sqp *sqp, struct ib_ud_wr *wr,
			    void *wqe, unsigned *mlx_seg_len)
{
	struct ib_device *ib_dev = sqp->qp.ibqp.device;
	struct mlx4_wqe_mlx_seg *mlx = wqe;
	struct mlx4_wqe_ctrl_seg *ctrl = wqe;
	struct mlx4_wqe_inline_seg *inl = wqe + sizeof *mlx;
	struct mlx4_ib_ah *ah = to_mah(wr->ah);
	union ib_gid sgid;
	u16 pkey;
	int send_size;
	int header_size;
	int spc;
	int i;
	int err = 0;
	u16 vlan = 0xffff;
	bool is_eth;
	bool is_vlan = false;
	bool is_grh;
	bool is_udp = false;
	int ip_version = 0;

	send_size = 0;
	for (i = 0; i < wr->wr.num_sge; ++i)
		send_size += wr->wr.sg_list[i].length;

	is_eth = rdma_port_get_link_layer(sqp->qp.ibqp.device, sqp->qp.port) == IB_LINK_LAYER_ETHERNET;
	is_grh = mlx4_ib_ah_grh_present(ah);
	if (is_eth) {
		struct ib_gid_attr gid_attr;

		if (mlx4_is_mfunc(to_mdev(ib_dev)->dev)) {
			/* When multi-function is enabled, the ib_core gid
			 * indexes don't necessarily match the hw ones, so
			 * we must use our own cache */
			err = mlx4_get_roce_gid_from_slave(to_mdev(ib_dev)->dev,
							   be32_to_cpu(ah->av.ib.port_pd) >> 24,
							   ah->av.ib.gid_index, &sgid.raw[0]);
			if (err)
				return err;
		} else  {
			err = ib_get_cached_gid(ib_dev,
						be32_to_cpu(ah->av.ib.port_pd) >> 24,
						ah->av.ib.gid_index, &sgid,
						&gid_attr);
			if (!err) {
				if (gid_attr.ndev)
					dev_put(gid_attr.ndev);
				if (!memcmp(&sgid, &zgid, sizeof(sgid)))
					err = -ENOENT;
			}
			if (!err) {
				is_udp = gid_attr.gid_type == IB_GID_TYPE_ROCE_UDP_ENCAP;
				if (is_udp) {
					if (ipv6_addr_v4mapped((struct in6_addr *)&sgid))
						ip_version = 4;
					else
						ip_version = 6;
					is_grh = false;
				}
			} else {
				return err;
			}
		}
		if (ah->av.eth.vlan != cpu_to_be16(0xffff)) {
			vlan = be16_to_cpu(ah->av.eth.vlan) & 0x0fff;
			is_vlan = 1;
		}
	}
	err = ib_ud_header_init(send_size, !is_eth, is_eth, is_vlan, is_grh,
			  ip_version, is_udp, 0, &sqp->ud_header);
	if (err)
		return err;

	if (!is_eth) {
		sqp->ud_header.lrh.service_level =
			be32_to_cpu(ah->av.ib.sl_tclass_flowlabel) >> 28;
		sqp->ud_header.lrh.destination_lid = ah->av.ib.dlid;
		sqp->ud_header.lrh.source_lid = cpu_to_be16(ah->av.ib.g_slid & 0x7f);
	}

	if (is_grh || (ip_version == 6)) {
		sqp->ud_header.grh.traffic_class =
			(be32_to_cpu(ah->av.ib.sl_tclass_flowlabel) >> 20) & 0xff;
		sqp->ud_header.grh.flow_label    =
			ah->av.ib.sl_tclass_flowlabel & cpu_to_be32(0xfffff);
		sqp->ud_header.grh.hop_limit     = ah->av.ib.hop_limit;
		if (is_eth) {
			memcpy(sqp->ud_header.grh.source_gid.raw, sgid.raw, 16);
		} else {
			if (mlx4_is_mfunc(to_mdev(ib_dev)->dev)) {
				/* When multi-function is enabled, the ib_core gid
				 * indexes don't necessarily match the hw ones, so
				 * we must use our own cache
				 */
				sqp->ud_header.grh.source_gid.global.subnet_prefix =
					cpu_to_be64(atomic64_read(&(to_mdev(ib_dev)->sriov.
								    demux[sqp->qp.port - 1].
								    subnet_prefix)));
				sqp->ud_header.grh.source_gid.global.interface_id =
					to_mdev(ib_dev)->sriov.demux[sqp->qp.port - 1].
						       guid_cache[ah->av.ib.gid_index];
			} else {
				ib_get_cached_gid(ib_dev,
						  be32_to_cpu(ah->av.ib.port_pd) >> 24,
						  ah->av.ib.gid_index,
						  &sqp->ud_header.grh.source_gid, NULL);
			}
		}
		memcpy(sqp->ud_header.grh.destination_gid.raw,
		       ah->av.ib.dgid, 16);
	}

	if (ip_version == 4) {
		sqp->ud_header.ip4.tos =
			(be32_to_cpu(ah->av.ib.sl_tclass_flowlabel) >> 20) & 0xff;
		sqp->ud_header.ip4.id = 0;
		sqp->ud_header.ip4.frag_off = htons(IP_DF);
		sqp->ud_header.ip4.ttl = ah->av.eth.hop_limit;

		memcpy(&sqp->ud_header.ip4.saddr,
		       sgid.raw + 12, 4);
		memcpy(&sqp->ud_header.ip4.daddr, ah->av.ib.dgid + 12, 4);
		sqp->ud_header.ip4.check = ib_ud_ip4_csum(&sqp->ud_header);
	}

	if (is_udp) {
		sqp->ud_header.udp.dport = htons(ROCE_V2_UDP_DPORT);
		sqp->ud_header.udp.sport = htons(MLX4_ROCEV2_QP1_SPORT);
		sqp->ud_header.udp.csum = 0;
	}

	mlx->flags &= cpu_to_be32(MLX4_WQE_CTRL_CQ_UPDATE);

	if (!is_eth) {
		mlx->flags |= cpu_to_be32((!sqp->qp.ibqp.qp_num ? MLX4_WQE_MLX_VL15 : 0) |
					  (sqp->ud_header.lrh.destination_lid ==
					   IB_LID_PERMISSIVE ? MLX4_WQE_MLX_SLR : 0) |
					  (sqp->ud_header.lrh.service_level << 8));
		if (ah->av.ib.port_pd & cpu_to_be32(0x80000000))
			mlx->flags |= cpu_to_be32(0x1); /* force loopback */
		mlx->rlid = sqp->ud_header.lrh.destination_lid;
	}

	switch (wr->wr.opcode) {
	case IB_WR_SEND:
		sqp->ud_header.bth.opcode	 = IB_OPCODE_UD_SEND_ONLY;
		sqp->ud_header.immediate_present = 0;
		break;
	case IB_WR_SEND_WITH_IMM:
		sqp->ud_header.bth.opcode	 = IB_OPCODE_UD_SEND_ONLY_WITH_IMMEDIATE;
		sqp->ud_header.immediate_present = 1;
		sqp->ud_header.immediate_data    = wr->wr.ex.imm_data;
		break;
	default:
		return -EINVAL;
	}

	if (is_eth) {
		struct in6_addr in6;
		u16 ether_type;
		u16 pcp = (be32_to_cpu(ah->av.ib.sl_tclass_flowlabel) >> 29) << 13;

		ether_type = (!is_udp) ? MLX4_IB_IBOE_ETHERTYPE :
			(ip_version == 4 ? ETHERTYPE_IP : ETHERTYPE_IPV6);

		mlx->sched_prio = cpu_to_be16(pcp);

		ether_addr_copy(sqp->ud_header.eth.smac_h, ah->av.eth.s_mac);
		memcpy(sqp->ud_header.eth.dmac_h, ah->av.eth.mac, 6);
		memcpy(&ctrl->srcrb_flags16[0], ah->av.eth.mac, 2);
		memcpy(&ctrl->imm, ah->av.eth.mac + 2, 4);
		memcpy(&in6, sgid.raw, sizeof(in6));


		if (!memcmp(sqp->ud_header.eth.smac_h, sqp->ud_header.eth.dmac_h, 6))
			mlx->flags |= cpu_to_be32(MLX4_WQE_CTRL_FORCE_LOOPBACK);
		if (!is_vlan) {
			sqp->ud_header.eth.type = cpu_to_be16(ether_type);
		} else {
			sqp->ud_header.vlan.type = cpu_to_be16(ether_type);
			sqp->ud_header.vlan.tag = cpu_to_be16(vlan | pcp);
		}
	} else {
		sqp->ud_header.lrh.virtual_lane    = !sqp->qp.ibqp.qp_num ? 15 :
							sl_to_vl(to_mdev(ib_dev),
								 sqp->ud_header.lrh.service_level,
								 sqp->qp.port);
		if (sqp->qp.ibqp.qp_num && sqp->ud_header.lrh.virtual_lane == 15)
			return -EINVAL;
		if (sqp->ud_header.lrh.destination_lid == IB_LID_PERMISSIVE)
			sqp->ud_header.lrh.source_lid = IB_LID_PERMISSIVE;
	}
	sqp->ud_header.bth.solicited_event = !!(wr->wr.send_flags & IB_SEND_SOLICITED);
	if (!sqp->qp.ibqp.qp_num)
		ib_get_cached_pkey(ib_dev, sqp->qp.port, sqp->pkey_index, &pkey);
	else
		ib_get_cached_pkey(ib_dev, sqp->qp.port, wr->pkey_index, &pkey);
	sqp->ud_header.bth.pkey = cpu_to_be16(pkey);
	sqp->ud_header.bth.destination_qpn = cpu_to_be32(wr->remote_qpn);
	sqp->ud_header.bth.psn = cpu_to_be32((sqp->send_psn++) & ((1 << 24) - 1));
	sqp->ud_header.deth.qkey = cpu_to_be32(wr->remote_qkey & 0x80000000 ?
					       sqp->qkey : wr->remote_qkey);
	sqp->ud_header.deth.source_qpn = cpu_to_be32(sqp->qp.ibqp.qp_num);

	header_size = ib_ud_header_pack(&sqp->ud_header, sqp->header_buf);

	if (0) {
		pr_err("built UD header of size %d:\n", header_size);
		for (i = 0; i < header_size / 4; ++i) {
			if (i % 8 == 0)
				pr_err("  [%02x] ", i * 4);
			pr_cont(" %08x",
				be32_to_cpu(((__be32 *) sqp->header_buf)[i]));
			if ((i + 1) % 8 == 0)
				pr_cont("\n");
		}
		pr_err("\n");
	}

	/*
	 * Inline data segments may not cross a 64 byte boundary.  If
	 * our UD header is bigger than the space available up to the
	 * next 64 byte boundary in the WQE, use two inline data
	 * segments to hold the UD header.
	 */
	spc = MLX4_INLINE_ALIGN -
		((unsigned long) (inl + 1) & (MLX4_INLINE_ALIGN - 1));
	if (header_size <= spc) {
		inl->byte_count = cpu_to_be32(1U << 31 | header_size);
		memcpy(inl + 1, sqp->header_buf, header_size);
		i = 1;
	} else {
		inl->byte_count = cpu_to_be32(1U << 31 | spc);
		memcpy(inl + 1, sqp->header_buf, spc);

		inl = (void *) (inl + 1) + spc;
		memcpy(inl + 1, sqp->header_buf + spc, header_size - spc);
		/*
		 * Need a barrier here to make sure all the data is
		 * visible before the byte_count field is set.
		 * Otherwise the HCA prefetcher could grab the 64-byte
		 * chunk with this inline segment and get a valid (!=
		 * 0xffffffff) byte count but stale data, and end up
		 * generating a packet with bad headers.
		 *
		 * The first inline segment's byte_count field doesn't
		 * need a barrier, because it comes after a
		 * control/MLX segment and therefore is at an offset
		 * of 16 mod 64.
		 */
		wmb();
		inl->byte_count = cpu_to_be32(1U << 31 | (header_size - spc));
		i = 2;
	}

	*mlx_seg_len =
		ALIGN(i * sizeof (struct mlx4_wqe_inline_seg) + header_size, 16);
	return 0;
}