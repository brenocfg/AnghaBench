#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct part_conf {TYPE_2__* p_subn; } ;
struct TYPE_8__ {int /*<<< orphan*/  part_guid_tbl; int /*<<< orphan*/  full_guid_tbl; } ;
typedef  TYPE_3__ osm_prtn_t ;
struct TYPE_9__ {int /*<<< orphan*/  p_node; } ;
typedef  TYPE_4__ osm_physp_t ;
typedef  scalar_t__ membership_t ;
typedef  int /*<<< orphan*/  ib_net64_t ;
typedef  int /*<<< orphan*/  cl_map_t ;
typedef  int /*<<< orphan*/  cl_map_iterator_t ;
struct TYPE_6__ {int /*<<< orphan*/  allow_both_pkeys; } ;
struct TYPE_7__ {TYPE_1__ opt; } ;

/* Variables and functions */
 scalar_t__ BOTH ; 
#define  IB_NODE_TYPE_CA 130 
#define  IB_NODE_TYPE_ROUTER 129 
#define  IB_NODE_TYPE_SWITCH 128 
 scalar_t__ LIMITED ; 
 int /*<<< orphan*/  cl_hton64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_map_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_map_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_map_next (int /*<<< orphan*/ ) ; 
 scalar_t__ cl_map_obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_map_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_map_remove_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_map_remove_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int osm_node_get_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void manage_membership_change(struct part_conf *conf, osm_prtn_t * p,
				     unsigned type, membership_t membership,
				     ib_net64_t guid)
{
	cl_map_t *p_tbl;
	cl_map_iterator_t p_next, p_item;
	osm_physp_t *p_physp;

	/* In allow_both_pkeys mode */
	/* if membership of the PKEY is set to FULL */
	/* need to clean up the part_guid_tbl table entry for this guid */
	/* if membership of the PKEY is set to LIMITED */
	/* need to clean up the full_guid_tbl table entry for this guid */
	/* as it could be populated because of previous definitions */

	if (!conf->p_subn->opt.allow_both_pkeys || membership == BOTH)
		return;

	switch (type){
	/* ALL = 0 */
	case 0:
		cl_map_remove_all(membership == LIMITED ?
				  &p->full_guid_tbl : &p->part_guid_tbl);
		break;
	/* specific GUID */
	case 0xFF:
		cl_map_remove(membership == LIMITED ?
			      &p->full_guid_tbl : &p->part_guid_tbl,
			      cl_hton64(guid));
		break;

	case IB_NODE_TYPE_CA:
	case IB_NODE_TYPE_SWITCH:
	case IB_NODE_TYPE_ROUTER:
		p_tbl = (membership == LIMITED) ?
			 &p->full_guid_tbl : &p->part_guid_tbl;

		p_next = cl_map_head(p_tbl);
		while (p_next != cl_map_end(p_tbl)) {
			p_item = p_next;
			p_next = cl_map_next(p_item);
			p_physp = (osm_physp_t *) cl_map_obj(p_item);
			if (osm_node_get_type(p_physp->p_node) == type)
				cl_map_remove_item(p_tbl, p_item);
		}
		break;
	default:
		break;

	}
}