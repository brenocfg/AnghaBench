#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mgrp_mgid_tbl; } ;
typedef  TYPE_1__ osm_subn_t ;
struct TYPE_5__ {int /*<<< orphan*/  mlid; } ;
typedef  TYPE_2__ osm_mgrp_t ;
typedef  int /*<<< orphan*/  ib_net16_t ;
typedef  int /*<<< orphan*/  ib_gid_t ;

/* Variables and functions */
 scalar_t__ cl_fmap_end (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_fmap_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare_ipv6_snm_mgids ; 

__attribute__((used)) static ib_net16_t find_ipv6_snm_mlid(osm_subn_t *subn, ib_gid_t *mgid)
{
	osm_mgrp_t *m = (osm_mgrp_t *)cl_fmap_match(&subn->mgrp_mgid_tbl, mgid,
						    compare_ipv6_snm_mgids);
	if (m != (osm_mgrp_t *)cl_fmap_end(&subn->mgrp_mgid_tbl))
		return m->mlid;
	return 0;
}