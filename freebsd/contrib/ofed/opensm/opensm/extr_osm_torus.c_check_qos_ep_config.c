#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int max_vls; char* vlarb_high; char* vlarb_low; scalar_t__ sl2vl; } ;
typedef  TYPE_1__ osm_qos_options_t ;
typedef  int /*<<< orphan*/  osm_log_t ;

/* Variables and functions */
 char* OSM_DEFAULT_QOS_VLARB_HIGH ; 
 char* OSM_DEFAULT_QOS_VLARB_LOW ; 
 int /*<<< orphan*/  OSM_LOG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  OSM_LOG_INFO ; 
 int /*<<< orphan*/  check_ep_vlarb_config (char const*,int,int,char const*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void check_qos_ep_config(osm_qos_options_t *opt, osm_qos_options_t *def,
			 const char *str, osm_log_t *log)
{
	const char *vlarb_str;
	bool is_default, is_specific;
	unsigned max_vls;

	max_vls = def->max_vls;
	if (opt->max_vls > 0)
		max_vls = opt->max_vls;

	if (max_vls > 0 && max_vls < 2)
		OSM_LOG(log, OSM_LOG_INFO,
			"Warning: full torus-2QoS functionality not available "
			"for configured %s_max_vls = %d\n",
			(opt->max_vls > 0 ? str : "qos"), opt->max_vls);

	vlarb_str = opt->vlarb_high;
	is_default = false;
	is_specific = true;
	if (!vlarb_str) {
		vlarb_str = def->vlarb_high;
		is_specific = false;
	}
	if (!vlarb_str) {
		vlarb_str = OSM_DEFAULT_QOS_VLARB_HIGH;
		is_default = true;
	}
	check_ep_vlarb_config(vlarb_str, is_default, is_specific,
			      str, "high", log);

	vlarb_str = opt->vlarb_low;
	is_default = false;
	is_specific = true;
	if (!vlarb_str) {
		vlarb_str = def->vlarb_low;
		is_specific = false;
	}
	if (!vlarb_str) {
		vlarb_str = OSM_DEFAULT_QOS_VLARB_LOW;
		is_default = true;
	}
	check_ep_vlarb_config(vlarb_str, is_default, is_specific,
			      str, "low", log);

	if (opt->sl2vl)
		OSM_LOG(log, OSM_LOG_INFO,
			"Warning: torus-2QoS must override configured "
			"%s_sl2vl to generate deadlock-free routes\n", str);
}