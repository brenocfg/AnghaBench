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
typedef  scalar_t__ uint16_t ;
struct table_info {scalar_t__ data; } ;
struct ip_fw_chain {int dummy; } ;
struct iftable_cfg {scalar_t__ used; int /*<<< orphan*/  main_ptr; struct table_info* ti; } ;
struct ifidx {int /*<<< orphan*/  value; scalar_t__ spare; scalar_t__ kidx; } ;
struct TYPE_4__ {TYPE_1__* iface; } ;
struct ifentry {int linked; TYPE_2__ ic; int /*<<< orphan*/  value; struct iftable_cfg* icfg; } ;
struct TYPE_3__ {scalar_t__ ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int badd (scalar_t__*,struct ifidx*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int bdel (scalar_t__*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare_ifidx ; 

__attribute__((used)) static void
if_notifier(struct ip_fw_chain *ch, void *cbdata, uint16_t ifindex)
{
	struct ifentry *ife;
	struct ifidx ifi;
	struct iftable_cfg *icfg;
	struct table_info *ti;
	int res;

	ife = (struct ifentry *)cbdata;
	icfg = ife->icfg;
	ti = icfg->ti;

	KASSERT(ti != NULL, ("ti=NULL, check change_ti handler"));

	if (ife->linked == 0 && ifindex != 0) {
		/* Interface announce */
		ifi.kidx = ifindex;
		ifi.spare = 0;
		ifi.value = ife->value;
		res = badd(&ifindex, &ifi, icfg->main_ptr, icfg->used,
		    sizeof(struct ifidx), compare_ifidx);
		KASSERT(res == 1, ("index %d already exists", ifindex));
		icfg->used++;
		ti->data = icfg->used;
		ife->linked = 1;
	} else if (ife->linked != 0 && ifindex == 0) {
		/* Interface withdrawal */
		ifindex = ife->ic.iface->ifindex;

		res = bdel(&ifindex, icfg->main_ptr, icfg->used,
		    sizeof(struct ifidx), compare_ifidx);

		KASSERT(res == 1, ("index %d does not exist", ifindex));
		icfg->used--;
		ti->data = icfg->used;
		ife->linked = 0;
	}
}