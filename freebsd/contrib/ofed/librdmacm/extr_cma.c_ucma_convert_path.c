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
typedef  void* uint8_t ;
typedef  int uint32_t ;
struct ibv_sa_path_rec {int reversible; int numb_path; int sl; int mtu_selector; int mtu; int rate_selector; int rate; int packet_life_time_selector; int packet_life_time; void* preference; int /*<<< orphan*/  pkey; int /*<<< orphan*/  traffic_class; void* hop_limit; int /*<<< orphan*/  flow_label; scalar_t__ raw_traffic; int /*<<< orphan*/  slid; int /*<<< orphan*/  dlid; int /*<<< orphan*/  sgid; int /*<<< orphan*/  dgid; } ;
struct TYPE_2__ {int reversible_numpath; int mtu; int rate; int packetlifetime; int /*<<< orphan*/  qosclass_sl; int /*<<< orphan*/  pkey; int /*<<< orphan*/  tclass; int /*<<< orphan*/  flowlabel_hoplimit; int /*<<< orphan*/  slid; int /*<<< orphan*/  dlid; int /*<<< orphan*/  sgid; int /*<<< orphan*/  dgid; } ;
struct ibv_path_data {scalar_t__ flags; TYPE_1__ path; } ;

/* Variables and functions */
 int be16toh (int /*<<< orphan*/ ) ; 
 int be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htobe32 (int) ; 

__attribute__((used)) static void ucma_convert_path(struct ibv_path_data *path_data,
			      struct ibv_sa_path_rec *sa_path)
{
	uint32_t fl_hop;

	sa_path->dgid = path_data->path.dgid;
	sa_path->sgid = path_data->path.sgid;
	sa_path->dlid = path_data->path.dlid;
	sa_path->slid = path_data->path.slid;
	sa_path->raw_traffic = 0;

	fl_hop = be32toh(path_data->path.flowlabel_hoplimit);
	sa_path->flow_label = htobe32(fl_hop >> 8);
	sa_path->hop_limit = (uint8_t) fl_hop;

	sa_path->traffic_class = path_data->path.tclass;
	sa_path->reversible = path_data->path.reversible_numpath >> 7;
	sa_path->numb_path = 1;
	sa_path->pkey = path_data->path.pkey;
	sa_path->sl = be16toh(path_data->path.qosclass_sl) & 0xF;
	sa_path->mtu_selector = 2;	/* exactly */
	sa_path->mtu = path_data->path.mtu & 0x1F;
	sa_path->rate_selector = 2;
	sa_path->rate = path_data->path.rate & 0x1F;
	sa_path->packet_life_time_selector = 2;
	sa_path->packet_life_time = path_data->path.packetlifetime & 0x1F;

	sa_path->preference = (uint8_t) path_data->flags;
}