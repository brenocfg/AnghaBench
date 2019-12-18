#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_67__   TYPE_9__ ;
typedef  struct TYPE_66__   TYPE_8__ ;
typedef  struct TYPE_65__   TYPE_7__ ;
typedef  struct TYPE_64__   TYPE_6__ ;
typedef  struct TYPE_63__   TYPE_5__ ;
typedef  struct TYPE_62__   TYPE_4__ ;
typedef  struct TYPE_61__   TYPE_3__ ;
typedef  struct TYPE_60__   TYPE_30__ ;
typedef  struct TYPE_59__   TYPE_2__ ;
typedef  struct TYPE_58__   TYPE_22__ ;
typedef  struct TYPE_57__   TYPE_21__ ;
typedef  struct TYPE_56__   TYPE_20__ ;
typedef  struct TYPE_55__   TYPE_1__ ;
typedef  struct TYPE_54__   TYPE_19__ ;
typedef  struct TYPE_53__   TYPE_18__ ;
typedef  struct TYPE_52__   TYPE_17__ ;
typedef  struct TYPE_51__   TYPE_16__ ;
typedef  struct TYPE_50__   TYPE_15__ ;
typedef  struct TYPE_49__   TYPE_14__ ;
typedef  struct TYPE_48__   TYPE_13__ ;
typedef  struct TYPE_47__   TYPE_12__ ;
typedef  struct TYPE_46__   TYPE_11__ ;
typedef  struct TYPE_45__   TYPE_10__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  s_rec ;
typedef  int /*<<< orphan*/  rep_addr ;
typedef  int /*<<< orphan*/  osm_port_t ;
struct TYPE_54__ {void* dirty; } ;
struct TYPE_53__ {char* sa_db_file; void* no_clients_rereg; } ;
struct TYPE_60__ {TYPE_18__ opt; int /*<<< orphan*/  first_time_master_sweep; } ;
struct TYPE_61__ {scalar_t__ mlids_init_max; } ;
struct TYPE_56__ {TYPE_19__ sa; TYPE_30__ subn; int /*<<< orphan*/  log; TYPE_3__ sm; } ;
typedef  TYPE_20__ osm_opensm_t ;
struct TYPE_57__ {int /*<<< orphan*/  mcm_port_tbl; } ;
typedef  TYPE_21__ osm_mgrp_t ;
struct TYPE_52__ {void** guid; } ;
struct TYPE_50__ {void* remote_qp; void* remote_qkey; void* service_level; scalar_t__ pkey_ix; } ;
struct TYPE_51__ {TYPE_15__ gsi; } ;
struct TYPE_47__ {void* trap_num; void* qpn_resp_time_val; int /*<<< orphan*/  reserved2; } ;
struct TYPE_48__ {TYPE_12__ generic; } ;
struct TYPE_45__ {void* prefix; void* interface_id; } ;
struct TYPE_46__ {TYPE_10__ unicast; } ;
struct TYPE_49__ {void* lid_range_begin; void* lid_range_end; void* is_generic; void* subscribe; void* trap_type; TYPE_13__ g_or_v; TYPE_11__ gid; } ;
struct TYPE_66__ {void* prefix; void* interface_id; } ;
struct TYPE_67__ {TYPE_8__ unicast; } ;
struct TYPE_64__ {void* prefix; void* interface_id; } ;
struct TYPE_65__ {TYPE_6__ unicast; } ;
struct TYPE_62__ {void* prefix; void* interface_id; } ;
struct TYPE_63__ {TYPE_4__ unicast; } ;
struct TYPE_55__ {void* prefix; void* interface_id; } ;
struct TYPE_59__ {TYPE_1__ unicast; } ;
struct TYPE_58__ {void* qkey; void* mlid; void* mtu; void* tclass; void* pkey; void* rate; void* pkt_life; void* sl_flow_hop; void* scope_state; void* service_id; void* service_pkey; void* service_lease; void** service_name; void** service_data64; void* subscriber_enum; void* dest_lid; void* path_bits; void* static_rate; void* lid; void* block_num; TYPE_17__ guid_info; TYPE_16__ addr_type; TYPE_14__ inform_info; TYPE_9__ subscriber_gid; int /*<<< orphan*/ * service_data32; int /*<<< orphan*/ * service_data16; int /*<<< orphan*/ * service_data8; int /*<<< orphan*/ * service_key; TYPE_7__ service_gid; TYPE_5__ port_gid; void* proxy_join; TYPE_2__ mgid; } ;
typedef  TYPE_22__ osm_mad_addr_t ;
typedef  int /*<<< orphan*/  mcm_rec ;
typedef  int /*<<< orphan*/  line ;
typedef  TYPE_22__ ib_service_record_t ;
typedef  void* ib_net64_t ;
typedef  void* ib_net16_t ;
typedef  TYPE_22__ ib_member_rec_t ;
typedef  TYPE_22__ ib_inform_info_record_t ;
typedef  TYPE_22__ ib_guidinfo_record_t ;
typedef  int /*<<< orphan*/  i_rec ;
typedef  int /*<<< orphan*/  gi_rec ;
typedef  void* boolean_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int,char*,...) ; 
 int OSM_LOG_ERROR ; 
 int OSM_LOG_SYS ; 
 int OSM_LOG_VERBOSE ; 
 int /*<<< orphan*/  PARSE_AHEAD (char*,int /*<<< orphan*/ ,char*,void**) ; 
 scalar_t__ cl_ntoh16 (void*) ; 
 int /*<<< orphan*/  cl_ntoh32 (void*) ; 
 scalar_t__ cl_qmap_end (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_qmap_get (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ isspace (char) ; 
 scalar_t__ load_guidinfo (TYPE_20__*,void*,TYPE_22__*) ; 
 scalar_t__ load_infr (TYPE_20__*,TYPE_22__*,TYPE_22__*) ; 
 TYPE_21__* load_mcgroup (TYPE_20__*,void*,TYPE_22__*) ; 
 scalar_t__ load_svcr (TYPE_20__*,TYPE_22__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_22__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  net16 ; 
 int /*<<< orphan*/  net32 ; 
 int /*<<< orphan*/  net64 ; 
 int /*<<< orphan*/  net8 ; 
 int /*<<< orphan*/ * osm_get_port_by_alias_guid (TYPE_30__*,void*) ; 
 int /*<<< orphan*/  osm_mgrp_add_port (TYPE_30__*,int /*<<< orphan*/ *,TYPE_21__*,int /*<<< orphan*/ *,TYPE_22__*,void*) ; 
 int /*<<< orphan*/  sa_db_file_load_handle_mgrp (TYPE_20__*,TYPE_21__*) ; 
 int /*<<< orphan*/  string64 ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

int osm_sa_db_file_load(osm_opensm_t * p_osm)
{
	char line[1024];
	char *file_name;
	FILE *file;
	int ret = 0;
	osm_mgrp_t *p_next_mgrp = NULL;
	osm_mgrp_t *p_prev_mgrp = NULL;
	unsigned rereg_clients = 0;
	unsigned lineno;

	if (!p_osm->subn.first_time_master_sweep) {
		OSM_LOG(&p_osm->log, OSM_LOG_VERBOSE,
			"Not first sweep - skip SA DB restore\n");
		return 0;
	}

	file_name = p_osm->subn.opt.sa_db_file;
	if (!file_name) {
		OSM_LOG(&p_osm->log, OSM_LOG_VERBOSE,
			"sa db file name is not specified. Skip restore\n");
		return 0;
	}

	file = fopen(file_name, "r");
	if (!file) {
		OSM_LOG(&p_osm->log, OSM_LOG_ERROR | OSM_LOG_SYS, "ERR 4C02: "
			"Can't open sa db file \'%s\'. Skip restoring\n",
			file_name);
		return -1;
	}

	OSM_LOG(&p_osm->log, OSM_LOG_VERBOSE,
		"Restoring SA DB from file \'%s\'\n",
		file_name);

	lineno = 0;

	while (fgets(line, sizeof(line) - 1, file) != NULL) {
		char *p;
		uint8_t val;

		lineno++;

		p = line;
		while (isspace(*p))
			p++;

		if (*p == '#')
			continue;

		if (!strncmp(p, "MC Group", 8)) {
			ib_member_rec_t mcm_rec;
			ib_net16_t mlid;

			p_next_mgrp = NULL;
			memset(&mcm_rec, 0, sizeof(mcm_rec));

			PARSE_AHEAD(p, net16, " 0x", &mlid);
			PARSE_AHEAD(p, net64, " mgid=0x",
				    &mcm_rec.mgid.unicast.prefix);
			PARSE_AHEAD(p, net64, ":0x",
				    &mcm_rec.mgid.unicast.interface_id);
			PARSE_AHEAD(p, net64, " port_gid=0x",
				    &mcm_rec.port_gid.unicast.prefix);
			PARSE_AHEAD(p, net64, ":0x",
				    &mcm_rec.port_gid.unicast.interface_id);
			PARSE_AHEAD(p, net32, " qkey=0x", &mcm_rec.qkey);
			PARSE_AHEAD(p, net16, " mlid=0x", &mcm_rec.mlid);
			PARSE_AHEAD(p, net8, " mtu=0x", &mcm_rec.mtu);
			PARSE_AHEAD(p, net8, " tclass=0x", &mcm_rec.tclass);
			PARSE_AHEAD(p, net16, " pkey=0x", &mcm_rec.pkey);
			PARSE_AHEAD(p, net8, " rate=0x", &mcm_rec.rate);
			PARSE_AHEAD(p, net8, " pkt_life=0x", &mcm_rec.pkt_life);
			PARSE_AHEAD(p, net32, " sl_flow_hop=0x",
				    &mcm_rec.sl_flow_hop);
			PARSE_AHEAD(p, net8, " scope_state=0x",
				    &mcm_rec.scope_state);
			PARSE_AHEAD(p, net8, " proxy_join=0x", &val);
			mcm_rec.proxy_join = val;

			p_next_mgrp = load_mcgroup(p_osm, mlid, &mcm_rec);
			if (!p_next_mgrp)
				rereg_clients = 1;
			if (cl_ntoh16(mlid) > p_osm->sm.mlids_init_max)
				p_osm->sm.mlids_init_max = cl_ntoh16(mlid);
		} else if (p_next_mgrp && !strncmp(p, "mcm_port", 8)) {
			ib_member_rec_t mcmr;
			ib_net64_t guid;
			osm_port_t *port;
			boolean_t proxy;

			PARSE_AHEAD(p, net64, " port_gid=0x",
				    &mcmr.port_gid.unicast.prefix);
			PARSE_AHEAD(p, net64, ":0x",
				    &mcmr.port_gid.unicast.interface_id);
			PARSE_AHEAD(p, net8, " scope_state=0x", &mcmr.scope_state);
			PARSE_AHEAD(p, net8, " proxy_join=0x", &val);
			proxy = val;

			guid = mcmr.port_gid.unicast.interface_id;
			port = osm_get_port_by_alias_guid(&p_osm->subn, guid);
			if (port &&
			    cl_qmap_get(&p_next_mgrp->mcm_port_tbl, guid) ==
			    cl_qmap_end(&p_next_mgrp->mcm_port_tbl) &&
			    !osm_mgrp_add_port(&p_osm->subn, &p_osm->log,
						p_next_mgrp, port, &mcmr, proxy))
				rereg_clients = 1;
		} else if (!strncmp(p, "Service Record:", 15)) {
			ib_service_record_t s_rec;
			uint32_t modified_time, lease_period;

			p_next_mgrp = NULL;
			memset(&s_rec, 0, sizeof(s_rec));

			PARSE_AHEAD(p, net64, " id=0x", &s_rec.service_id);
			PARSE_AHEAD(p, net64, " gid=0x",
				    &s_rec.service_gid.unicast.prefix);
			PARSE_AHEAD(p, net64, ":0x",
				    &s_rec.service_gid.unicast.interface_id);
			PARSE_AHEAD(p, net16, " pkey=0x", &s_rec.service_pkey);
			PARSE_AHEAD(p, net32, " lease=0x",
				    &s_rec.service_lease);
			PARSE_AHEAD(p, net64, " key=0x",
				    (ib_net64_t *) (&s_rec.service_key[0]));
			PARSE_AHEAD(p, net64, ":0x",
				    (ib_net64_t *) (&s_rec.service_key[8]));
			PARSE_AHEAD(p, string64, " name=", s_rec.service_name);
			PARSE_AHEAD(p, net64, " data8=0x",
				    (ib_net64_t *) (&s_rec.service_data8[0]));
			PARSE_AHEAD(p, net64, ":0x",
				    (ib_net64_t *) (&s_rec.service_data8[8]));
			PARSE_AHEAD(p, net64, " data16=0x",
				    (ib_net64_t *) (&s_rec.service_data16[0]));
			PARSE_AHEAD(p, net64, ":0x",
				    (ib_net64_t *) (&s_rec.service_data16[4]));
			PARSE_AHEAD(p, net64, " data32=0x",
				    (ib_net64_t *) (&s_rec.service_data32[0]));
			PARSE_AHEAD(p, net64, ":0x",
				    (ib_net64_t *) (&s_rec.service_data32[2]));
			PARSE_AHEAD(p, net64, " data64=0x",
				    &s_rec.service_data64[0]);
			PARSE_AHEAD(p, net64, ":0x", &s_rec.service_data64[1]);
			PARSE_AHEAD(p, net32, " modified_time=0x",
				    &modified_time);
			PARSE_AHEAD(p, net32, " lease_period=0x",
				    &lease_period);

			if (load_svcr(p_osm, &s_rec, cl_ntoh32(modified_time),
				      cl_ntoh32(lease_period)))
				rereg_clients = 1;
		} else if (!strncmp(p, "InformInfo Record:", 18)) {
			ib_inform_info_record_t i_rec;
			osm_mad_addr_t rep_addr;
			ib_net16_t val16;

			p_next_mgrp = NULL;
			memset(&i_rec, 0, sizeof(i_rec));
			memset(&rep_addr, 0, sizeof(rep_addr));

			PARSE_AHEAD(p, net64, " subscriber_gid=0x",
				    &i_rec.subscriber_gid.unicast.prefix);
			PARSE_AHEAD(p, net64, ":0x",
				    &i_rec.subscriber_gid.unicast.interface_id);
			PARSE_AHEAD(p, net16, " subscriber_enum=0x",
				    &i_rec.subscriber_enum);
			PARSE_AHEAD(p, net64, " gid=0x",
				    &i_rec.inform_info.gid.unicast.prefix);
			PARSE_AHEAD(p, net64, ":0x",
				    &i_rec.inform_info.gid.unicast.
				    interface_id);
			PARSE_AHEAD(p, net16, " lid_range_begin=0x",
				    &i_rec.inform_info.lid_range_begin);
			PARSE_AHEAD(p, net16, " lid_range_end=0x",
				    &i_rec.inform_info.lid_range_end);
			PARSE_AHEAD(p, net8, " is_generic=0x",
				    &i_rec.inform_info.is_generic);
			PARSE_AHEAD(p, net8, " subscribe=0x",
				    &i_rec.inform_info.subscribe);
			PARSE_AHEAD(p, net16, " trap_type=0x",
				    &i_rec.inform_info.trap_type);
			PARSE_AHEAD(p, net16, " trap_num=0x",
				    &i_rec.inform_info.g_or_v.generic.trap_num);
			PARSE_AHEAD(p, net32, " qpn_resp_time_val=0x",
				    &i_rec.inform_info.g_or_v.generic.
				    qpn_resp_time_val);
			PARSE_AHEAD(p, net32, " node_type=0x",
				    (uint32_t *) & i_rec.inform_info.g_or_v.
				    generic.reserved2);

			PARSE_AHEAD(p, net16, " rep_addr: lid=0x",
				    &rep_addr.dest_lid);
			PARSE_AHEAD(p, net8, " path_bits=0x",
				    &rep_addr.path_bits);
			PARSE_AHEAD(p, net8, " static_rate=0x",
				    &rep_addr.static_rate);
			PARSE_AHEAD(p, net32, " remote_qp=0x",
				    &rep_addr.addr_type.gsi.remote_qp);
			PARSE_AHEAD(p, net32, " remote_qkey=0x",
				    &rep_addr.addr_type.gsi.remote_qkey);
			PARSE_AHEAD(p, net16, " pkey_ix=0x", &val16);
			rep_addr.addr_type.gsi.pkey_ix = cl_ntoh16(val16);
			PARSE_AHEAD(p, net8, " sl=0x",
				    &rep_addr.addr_type.gsi.service_level);

			if (load_infr(p_osm, &i_rec, &rep_addr))
				rereg_clients = 1;
		} else if (!strncmp(p, "GUIDInfo Record:", 16)) {
			ib_guidinfo_record_t gi_rec;
			ib_net64_t base_guid;

			p_next_mgrp = NULL;
			memset(&gi_rec, 0, sizeof(gi_rec));

			PARSE_AHEAD(p, net64, " base_guid=0x", &base_guid);
			PARSE_AHEAD(p, net16, " lid=0x", &gi_rec.lid);
			PARSE_AHEAD(p, net8, " block_num=0x",
				    &gi_rec.block_num);
			PARSE_AHEAD(p, net64, " guid0=0x",
				    &gi_rec.guid_info.guid[0]);
			PARSE_AHEAD(p, net64, " guid1=0x",
				    &gi_rec.guid_info.guid[1]);
			PARSE_AHEAD(p, net64, " guid2=0x",
				    &gi_rec.guid_info.guid[2]);
			PARSE_AHEAD(p, net64, " guid3=0x",
				    &gi_rec.guid_info.guid[3]);
			PARSE_AHEAD(p, net64, " guid4=0x",
				    &gi_rec.guid_info.guid[4]);
			PARSE_AHEAD(p, net64, " guid5=0x",
				    &gi_rec.guid_info.guid[5]);
			PARSE_AHEAD(p, net64, " guid6=0x",
				    &gi_rec.guid_info.guid[6]);
			PARSE_AHEAD(p, net64, " guid7=0x",
				    &gi_rec.guid_info.guid[7]);

			if (load_guidinfo(p_osm, base_guid, &gi_rec))
				rereg_clients = 1;
		}

		/*
		 * p_next_mgrp points to the multicast group now being parsed.
		 * p_prev_mgrp points to the last multicast group we parsed.
		 * We decide whether to keep or delete each multicast group
		 * only when we finish parsing it's member records. if the
		 * group has full members, or it is a "well known group" we
		 * keep it.
		 */
		if (p_prev_mgrp != p_next_mgrp) {
			if (p_prev_mgrp)
				sa_db_file_load_handle_mgrp(p_osm, p_prev_mgrp);
			p_prev_mgrp = p_next_mgrp;
		}
	}

	if (p_next_mgrp)
		sa_db_file_load_handle_mgrp(p_osm, p_prev_mgrp);

	/*
	 * If loading succeeded, do whatever 'no_clients_rereg' says.
	 * If loading failed at some point, turn off the 'no_clients_rereg'
	 * option (turn on re-registration requests).
	 */
	if (rereg_clients)
		p_osm->subn.opt.no_clients_rereg = FALSE;

	/* We've just finished loading SA DB file - clear the "dirty" flag */
	p_osm->sa.dirty = FALSE;

_error:
	fclose(file);
	return ret;
}