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
struct ib_user_path_rec {int /*<<< orphan*/  packet_life_time_selector; int /*<<< orphan*/  preference; int /*<<< orphan*/  packet_life_time; int /*<<< orphan*/  rate; int /*<<< orphan*/  rate_selector; int /*<<< orphan*/  mtu; int /*<<< orphan*/  mtu_selector; int /*<<< orphan*/  sl; int /*<<< orphan*/  pkey; int /*<<< orphan*/  numb_path; int /*<<< orphan*/  reversible; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  raw_traffic; int /*<<< orphan*/  slid; int /*<<< orphan*/  dlid; int /*<<< orphan*/  sgid; int /*<<< orphan*/  dgid; } ;
struct TYPE_4__ {int /*<<< orphan*/  raw; } ;
struct TYPE_3__ {int /*<<< orphan*/  raw; } ;
struct ib_sa_path_rec {int /*<<< orphan*/  gid_type; scalar_t__ ifindex; int /*<<< orphan*/  net; int /*<<< orphan*/  dmac; int /*<<< orphan*/  packet_life_time_selector; int /*<<< orphan*/  preference; int /*<<< orphan*/  packet_life_time; int /*<<< orphan*/  rate; int /*<<< orphan*/  rate_selector; int /*<<< orphan*/  mtu; int /*<<< orphan*/  mtu_selector; int /*<<< orphan*/  sl; int /*<<< orphan*/  pkey; int /*<<< orphan*/  numb_path; int /*<<< orphan*/  reversible; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  raw_traffic; int /*<<< orphan*/  slid; int /*<<< orphan*/  dlid; TYPE_2__ sgid; TYPE_1__ dgid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_GID_TYPE_IB ; 
 int /*<<< orphan*/  TD_TO_VNET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void ib_copy_path_rec_from_user(struct ib_sa_path_rec *dst,
				struct ib_user_path_rec *src)
{
	memcpy(dst->dgid.raw, src->dgid, sizeof dst->dgid);
	memcpy(dst->sgid.raw, src->sgid, sizeof dst->sgid);

	dst->dlid		= src->dlid;
	dst->slid		= src->slid;
	dst->raw_traffic	= src->raw_traffic;
	dst->flow_label		= src->flow_label;
	dst->hop_limit		= src->hop_limit;
	dst->traffic_class	= src->traffic_class;
	dst->reversible		= src->reversible;
	dst->numb_path		= src->numb_path;
	dst->pkey		= src->pkey;
	dst->sl			= src->sl;
	dst->mtu_selector	= src->mtu_selector;
	dst->mtu		= src->mtu;
	dst->rate_selector	= src->rate_selector;
	dst->rate		= src->rate;
	dst->packet_life_time	= src->packet_life_time;
	dst->preference		= src->preference;
	dst->packet_life_time_selector = src->packet_life_time_selector;

	memset(dst->dmac, 0, sizeof(dst->dmac));
	dst->net = TD_TO_VNET(curthread);
	dst->ifindex = 0;
	dst->gid_type = IB_GID_TYPE_IB;
}