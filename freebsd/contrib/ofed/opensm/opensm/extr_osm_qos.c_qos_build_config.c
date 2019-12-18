#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
struct TYPE_9__ {int /*<<< orphan*/ * raw_vl_by_sl; } ;
struct qos_config {scalar_t__ max_vls; TYPE_3__ sl2vl; TYPE_2__* vlarb_low; TYPE_1__* vlarb_high; void* vl_high_limit; } ;
struct TYPE_10__ {scalar_t__ max_vls; scalar_t__ high_limit; char* vlarb_high; char* vlarb_low; char* sl2vl; } ;
typedef  TYPE_4__ osm_qos_options_t ;
struct TYPE_8__ {int /*<<< orphan*/ * vl_entry; } ;
struct TYPE_7__ {int /*<<< orphan*/ * vl_entry; } ;

/* Variables and functions */
 int IB_MAX_NUM_VLS ; 
 int IB_NUM_VL_ARB_ELEMENTS_IN_BLOCK ; 
 scalar_t__ OSM_DEFAULT_QOS_HIGH_LIMIT ; 
 scalar_t__ OSM_DEFAULT_QOS_MAX_VLS ; 
 char* OSM_DEFAULT_QOS_SL2VL ; 
 char* OSM_DEFAULT_QOS_VLARB_HIGH ; 
 char* OSM_DEFAULT_QOS_VLARB_LOW ; 
 int /*<<< orphan*/  memset (struct qos_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_sl2vl_entry (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_vlarb_entry (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qos_build_config(struct qos_config *cfg, osm_qos_options_t * opt,
			     osm_qos_options_t * dflt)
{
	int i;
	const char *p;

	memset(cfg, 0, sizeof(*cfg));

	if (opt->max_vls > 0)
		cfg->max_vls = opt->max_vls;
	else {
		if (dflt->max_vls > 0)
			cfg->max_vls = dflt->max_vls;
		else
			cfg->max_vls = OSM_DEFAULT_QOS_MAX_VLS;
	}

	if (opt->high_limit >= 0)
		cfg->vl_high_limit = (uint8_t) opt->high_limit;
	else {
		if (dflt->high_limit >= 0)
			cfg->vl_high_limit = (uint8_t) dflt->high_limit;
		else
			cfg->vl_high_limit = (uint8_t) OSM_DEFAULT_QOS_HIGH_LIMIT;
	}

	if (opt->vlarb_high)
		p = opt->vlarb_high;
	else {
		if (dflt->vlarb_high)
			p = dflt->vlarb_high;
		else
			p = OSM_DEFAULT_QOS_VLARB_HIGH;
	}
	for (i = 0; i < 2 * IB_NUM_VL_ARB_ELEMENTS_IN_BLOCK; i++) {
		p += parse_vlarb_entry(p,
				       &cfg->vlarb_high[i /
							IB_NUM_VL_ARB_ELEMENTS_IN_BLOCK].
				       vl_entry[i %
						IB_NUM_VL_ARB_ELEMENTS_IN_BLOCK]);
	}

	if (opt->vlarb_low)
		p = opt->vlarb_low;
	else {
		if (dflt->vlarb_low)
			p = dflt->vlarb_low;
		else
			p = OSM_DEFAULT_QOS_VLARB_LOW;
	}
	for (i = 0; i < 2 * IB_NUM_VL_ARB_ELEMENTS_IN_BLOCK; i++) {
		p += parse_vlarb_entry(p,
				       &cfg->vlarb_low[i /
						       IB_NUM_VL_ARB_ELEMENTS_IN_BLOCK].
				       vl_entry[i %
						IB_NUM_VL_ARB_ELEMENTS_IN_BLOCK]);
	}

	p = opt->sl2vl ? opt->sl2vl : dflt->sl2vl;
	if (opt->sl2vl)
		p = opt->sl2vl;
	else {
		if (dflt->sl2vl)
			p = dflt->sl2vl;
		else
			p = OSM_DEFAULT_QOS_SL2VL;
	}
	for (i = 0; i < IB_MAX_NUM_VLS / 2; i++)
		p += parse_sl2vl_entry(p, &cfg->sl2vl.raw_vl_by_sl[i]);
}