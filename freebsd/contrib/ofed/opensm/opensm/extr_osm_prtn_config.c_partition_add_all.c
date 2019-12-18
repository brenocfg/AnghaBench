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
struct part_conf {int /*<<< orphan*/  indx0; TYPE_2__* p_subn; int /*<<< orphan*/  p_log; } ;
typedef  int /*<<< orphan*/  osm_prtn_t ;
typedef  scalar_t__ membership_t ;
struct TYPE_3__ {scalar_t__ allow_both_pkeys; } ;
struct TYPE_4__ {TYPE_1__ opt; } ;

/* Variables and functions */
 scalar_t__ BOTH ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IB_SUCCESS ; 
 scalar_t__ LIMITED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  manage_membership_change (struct part_conf*,int /*<<< orphan*/ *,unsigned int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ osm_prtn_add_all (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int partition_add_all(struct part_conf *conf, osm_prtn_t * p,
			     unsigned type, membership_t membership)
{
	manage_membership_change(conf, p, type, membership, 0);

	if (membership != LIMITED &&
	    osm_prtn_add_all(conf->p_log, conf->p_subn, p, type, TRUE, conf->indx0) != IB_SUCCESS)
		return -1;
	if ((membership == LIMITED ||
	     (membership == BOTH && conf->p_subn->opt.allow_both_pkeys)) &&
	    osm_prtn_add_all(conf->p_log, conf->p_subn, p, type, FALSE, conf->indx0) != IB_SUCCESS)
		return -1;
	return 0;
}