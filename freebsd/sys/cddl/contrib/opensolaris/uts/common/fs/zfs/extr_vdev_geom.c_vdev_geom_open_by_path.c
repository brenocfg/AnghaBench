#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int vdev_path; } ;
typedef  TYPE_1__ vdev_t ;
struct g_provider {int dummy; } ;
struct g_consumer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 scalar_t__ FULL_MATCH ; 
 int /*<<< orphan*/  ZFS_LOG (int,char*,int) ; 
 struct g_provider* g_provider_by_name (int) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 scalar_t__ vdev_attach_ok (TYPE_1__*,struct g_provider*) ; 
 struct g_consumer* vdev_geom_attach (struct g_provider*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct g_consumer *
vdev_geom_open_by_path(vdev_t *vd, int check_guid)
{
	struct g_provider *pp;
	struct g_consumer *cp;

	g_topology_assert();

	cp = NULL;
	pp = g_provider_by_name(vd->vdev_path + sizeof("/dev/") - 1);
	if (pp != NULL) {
		ZFS_LOG(1, "Found provider by name %s.", vd->vdev_path);
		if (!check_guid || vdev_attach_ok(vd, pp) == FULL_MATCH)
			cp = vdev_geom_attach(pp, vd, B_FALSE);
	}

	return (cp);
}