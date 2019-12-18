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
struct TYPE_4__ {scalar_t__ sport; scalar_t__ dport; scalar_t__ vnic; scalar_t__ vlan; scalar_t__ macidx; scalar_t__ frag; scalar_t__ matchtype; scalar_t__ iport; scalar_t__ fcoe; scalar_t__ proto; scalar_t__ tos; scalar_t__ ethtype; int /*<<< orphan*/ * dip; int /*<<< orphan*/ * sip; } ;
struct TYPE_3__ {scalar_t__ ethtype; scalar_t__ tos; scalar_t__ proto; scalar_t__ fcoe; scalar_t__ iport; scalar_t__ matchtype; scalar_t__ frag; scalar_t__ macidx; scalar_t__ vlan_vld; scalar_t__ ovlan_vld; scalar_t__ pfvf_vld; } ;
struct t4_filter_specification {scalar_t__ type; TYPE_2__ val; TYPE_1__ mask; scalar_t__ hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool
filter_eq(struct t4_filter_specification *fs1,
    struct t4_filter_specification *fs2)
{
	int n;

	MPASS(fs1->hash && fs2->hash);

	if (fs1->type != fs2->type)
		return (false);

	n = fs1->type ? 16 : 4;
	if (bcmp(&fs1->val.sip[0], &fs2->val.sip[0], n) ||
	    bcmp(&fs1->val.dip[0], &fs2->val.dip[0], n) ||
	    fs1->val.sport != fs2->val.sport ||
	    fs1->val.dport != fs2->val.dport)
		return (false);

	/*
	 * We know the masks are the same because all hashfilter masks have to
	 * conform to the global tp->hash_filter_mask and the driver has
	 * verified that already.
	 */

	if ((fs1->mask.pfvf_vld || fs1->mask.ovlan_vld) &&
	    fs1->val.vnic != fs2->val.vnic)
		return (false);
	if (fs1->mask.vlan_vld && fs1->val.vlan != fs2->val.vlan)
		return (false);
	if (fs1->mask.macidx && fs1->val.macidx != fs2->val.macidx)
		return (false);
	if (fs1->mask.frag && fs1->val.frag != fs2->val.frag)
		return (false);
	if (fs1->mask.matchtype && fs1->val.matchtype != fs2->val.matchtype)
		return (false);
	if (fs1->mask.iport && fs1->val.iport != fs2->val.iport)
		return (false);
	if (fs1->mask.fcoe && fs1->val.fcoe != fs2->val.fcoe)
		return (false);
	if (fs1->mask.proto && fs1->val.proto != fs2->val.proto)
		return (false);
	if (fs1->mask.tos && fs1->val.tos != fs2->val.tos)
		return (false);
	if (fs1->mask.ethtype && fs1->val.ethtype != fs2->val.ethtype)
		return (false);

	return (true);
}