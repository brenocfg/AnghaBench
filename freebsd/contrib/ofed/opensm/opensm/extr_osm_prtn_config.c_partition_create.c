#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_8__ {scalar_t__ sl; int /*<<< orphan*/  FlowLabel; int /*<<< orphan*/  TClass; scalar_t__ Q_Key; int /*<<< orphan*/  rate; int /*<<< orphan*/  mtu; } ;
struct TYPE_12__ {int /*<<< orphan*/ * raw; } ;
struct precreate_mgroup {TYPE_2__ flags; TYPE_6__ mgid; } ;
struct TYPE_9__ {scalar_t__ sl; int /*<<< orphan*/  FlowLabel; int /*<<< orphan*/  TClass; scalar_t__ Q_Key; int /*<<< orphan*/  rate; int /*<<< orphan*/  mtu; } ;
struct part_conf {TYPE_3__ flags; TYPE_4__* p_prtn; scalar_t__ is_ipoib; int /*<<< orphan*/  p_log; TYPE_5__* p_subn; } ;
typedef  int /*<<< orphan*/  pkey ;
typedef  int ib_net16_t ;
typedef  int /*<<< orphan*/  broadcast_mgroup ;
struct TYPE_7__ {int /*<<< orphan*/  qos; } ;
struct TYPE_11__ {TYPE_1__ opt; } ;
struct TYPE_10__ {int pkey; scalar_t__ sl; } ;

/* Variables and functions */
 int CL_HTON16 (int) ; 
 scalar_t__ OSM_DEFAULT_SL ; 
 scalar_t__ OSM_IPOIB_BROADCAST_MGRP_QKEY ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,char*) ; 
 int /*<<< orphan*/  OSM_LOG_DEBUG ; 
 int /*<<< orphan*/  __create_mgrp (struct part_conf*,struct precreate_mgroup*) ; 
 int cl_hton16 (int /*<<< orphan*/ ) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memset (struct precreate_mgroup*,int /*<<< orphan*/ ,int) ; 
 TYPE_6__ osm_ipoib_broadcast_mgid ; 
 TYPE_4__* osm_prtn_make_new (int /*<<< orphan*/ ,TYPE_5__*,char*,int) ; 
 scalar_t__ strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int partition_create(unsigned lineno, struct part_conf *conf,
			    char *name, char *id, char *flag, char *flag_val)
{
	ib_net16_t pkey;

	if (!id && name && isdigit(*name)) {
		id = name;
		name = NULL;
	}

	if (id) {
		char *end;

		pkey = cl_hton16((uint16_t)strtoul(id, &end, 0));
		if (end == id || *end)
			return -1;
	} else
		pkey = 0;

	conf->p_prtn = osm_prtn_make_new(conf->p_log, conf->p_subn,
					 name, pkey);
	if (!conf->p_prtn)
		return -1;

	if (!conf->p_subn->opt.qos && conf->flags.sl != OSM_DEFAULT_SL) {
		OSM_LOG(conf->p_log, OSM_LOG_DEBUG, "Overriding SL %d"
			" to default SL %d on partition %s"
			" as QoS is not enabled.\n",
			conf->flags.sl, OSM_DEFAULT_SL, name);
		conf->flags.sl = OSM_DEFAULT_SL;
	}
	conf->p_prtn->sl = (uint8_t) conf->flags.sl;

	if (conf->is_ipoib) {
		struct precreate_mgroup broadcast_mgroup;
		memset(&broadcast_mgroup, 0, sizeof(broadcast_mgroup));
		broadcast_mgroup.mgid = osm_ipoib_broadcast_mgid;
		pkey = CL_HTON16(0x8000) | conf->p_prtn->pkey;
		memcpy(&broadcast_mgroup.mgid.raw[4], &pkey , sizeof(pkey));
		broadcast_mgroup.flags.mtu = conf->flags.mtu;
		broadcast_mgroup.flags.rate = conf->flags.rate;
		broadcast_mgroup.flags.sl = conf->flags.sl;
		broadcast_mgroup.flags.Q_Key = conf->flags.Q_Key ?
						conf->flags.Q_Key :
						OSM_IPOIB_BROADCAST_MGRP_QKEY;
		broadcast_mgroup.flags.TClass = conf->flags.TClass;
		broadcast_mgroup.flags.FlowLabel = conf->flags.FlowLabel;
		__create_mgrp(conf, &broadcast_mgroup);
	}

	return 0;
}