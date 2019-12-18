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
typedef  int uint32_t ;
struct ibv_sa_path_rec {int hop_limit; int reversible; int mtu; int rate; int packet_life_time; int /*<<< orphan*/  preference; int /*<<< orphan*/  sl; int /*<<< orphan*/  pkey; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  slid; int /*<<< orphan*/  dlid; int /*<<< orphan*/  sgid; int /*<<< orphan*/  dgid; } ;
struct TYPE_2__ {int reversible_numpath; int mtu; int rate; int packetlifetime; int /*<<< orphan*/  qosclass_sl; int /*<<< orphan*/  pkey; int /*<<< orphan*/  tclass; int /*<<< orphan*/  flowlabel_hoplimit; int /*<<< orphan*/  slid; int /*<<< orphan*/  dlid; int /*<<< orphan*/  sgid; int /*<<< orphan*/  dgid; } ;
struct ibv_path_data {int /*<<< orphan*/  flags; TYPE_1__ path; } ;

/* Variables and functions */
 int be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htobe16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htobe32 (int) ; 
 int /*<<< orphan*/  memset (struct ibv_path_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rs_convert_sa_path(struct ibv_sa_path_rec *sa_path,
			       struct ibv_path_data *path_data)
{
	uint32_t fl_hop;

	memset(path_data, 0, sizeof(*path_data));
	path_data->path.dgid = sa_path->dgid;
	path_data->path.sgid = sa_path->sgid;
	path_data->path.dlid = sa_path->dlid;
	path_data->path.slid = sa_path->slid;
	fl_hop = be32toh(sa_path->flow_label) << 8;
	path_data->path.flowlabel_hoplimit = htobe32(fl_hop | sa_path->hop_limit);
	path_data->path.tclass = sa_path->traffic_class;
	path_data->path.reversible_numpath = sa_path->reversible << 7 | 1;
	path_data->path.pkey = sa_path->pkey;
	path_data->path.qosclass_sl = htobe16(sa_path->sl);
	path_data->path.mtu = sa_path->mtu | 2 << 6;	/* exactly */
	path_data->path.rate = sa_path->rate | 2 << 6;
	path_data->path.packetlifetime = sa_path->packet_life_time | 2 << 6;
	path_data->flags= sa_path->preference;
}