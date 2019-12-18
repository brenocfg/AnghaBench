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
struct namedobj_instance {int dummy; } ;
struct named_object {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  refcnt; } ;
struct ipfw_iface {int /*<<< orphan*/  gencnt; TYPE_1__ no; int /*<<< orphan*/  ifindex; scalar_t__ resolved; int /*<<< orphan*/  ifname; } ;
struct dump_iface_args {int /*<<< orphan*/  sd; } ;
struct TYPE_4__ {int /*<<< orphan*/  gencnt; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  ifindex; int /*<<< orphan*/  flags; int /*<<< orphan*/  ifname; } ;
typedef  TYPE_2__ ipfw_iface_info ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_IFFLAG_RESOLVED ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ipfw_get_sopt_space (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
export_iface_internal(struct namedobj_instance *ii, struct named_object *no,
    void *arg)
{
	ipfw_iface_info *i;
	struct dump_iface_args *da;
	struct ipfw_iface *iif;

	da = (struct dump_iface_args *)arg;

	i = (ipfw_iface_info *)ipfw_get_sopt_space(da->sd, sizeof(*i));
	KASSERT(i != NULL, ("previously checked buffer is not enough"));

	iif = (struct ipfw_iface *)no;

	strlcpy(i->ifname, iif->ifname, sizeof(i->ifname));
	if (iif->resolved)
		i->flags |= IPFW_IFFLAG_RESOLVED;
	i->ifindex = iif->ifindex;
	i->refcnt = iif->no.refcnt;
	i->gencnt = iif->gencnt;
	return (0);
}