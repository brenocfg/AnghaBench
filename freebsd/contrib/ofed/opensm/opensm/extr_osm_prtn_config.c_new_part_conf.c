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
struct TYPE_2__ {int /*<<< orphan*/  mtu; int /*<<< orphan*/  rate; int /*<<< orphan*/  sl; } ;
struct part_conf {int /*<<< orphan*/  indx0; int /*<<< orphan*/  membership; TYPE_1__ flags; scalar_t__ is_ipoib; int /*<<< orphan*/ * p_prtn; int /*<<< orphan*/ * p_subn; int /*<<< orphan*/ * p_log; } ;
typedef  int /*<<< orphan*/  osm_subn_t ;
typedef  int /*<<< orphan*/  osm_log_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LIMITED ; 
 int /*<<< orphan*/  OSM_DEFAULT_MGRP_MTU ; 
 int /*<<< orphan*/  OSM_DEFAULT_MGRP_RATE ; 
 int /*<<< orphan*/  OSM_DEFAULT_SL ; 
 int /*<<< orphan*/  memset (struct part_conf*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct part_conf *new_part_conf(osm_log_t * p_log, osm_subn_t * p_subn)
{
	static struct part_conf part;
	struct part_conf *conf = &part;

	memset(conf, 0, sizeof(*conf));
	conf->p_log = p_log;
	conf->p_subn = p_subn;
	conf->p_prtn = NULL;
	conf->is_ipoib = 0;
	conf->flags.sl = OSM_DEFAULT_SL;
	conf->flags.rate = OSM_DEFAULT_MGRP_RATE;
	conf->flags.mtu = OSM_DEFAULT_MGRP_MTU;
	conf->membership = LIMITED;
	conf->indx0 = FALSE;
	return conf;
}