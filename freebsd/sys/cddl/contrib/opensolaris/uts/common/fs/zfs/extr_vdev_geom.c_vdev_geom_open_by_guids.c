#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* vdev_path; scalar_t__ vdev_guid; int /*<<< orphan*/  vdev_spa; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
struct g_consumer {TYPE_1__* provider; } ;
struct TYPE_5__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  ZFS_LOG (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 char* kmem_alloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 
 scalar_t__ spa_guid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_strfree (char*) ; 
 int strlen (char*) ; 
 struct g_consumer* vdev_geom_attach_by_guids (TYPE_2__*) ; 

__attribute__((used)) static struct g_consumer *
vdev_geom_open_by_guids(vdev_t *vd)
{
	struct g_consumer *cp;
	char *buf;
	size_t len;

	g_topology_assert();

	ZFS_LOG(1, "Searching by guids [%ju:%ju].",
		(uintmax_t)spa_guid(vd->vdev_spa), (uintmax_t)vd->vdev_guid);
	cp = vdev_geom_attach_by_guids(vd);
	if (cp != NULL) {
		len = strlen(cp->provider->name) + strlen("/dev/") + 1;
		buf = kmem_alloc(len, KM_SLEEP);

		snprintf(buf, len, "/dev/%s", cp->provider->name);
		spa_strfree(vd->vdev_path);
		vd->vdev_path = buf;

		ZFS_LOG(1, "Attach by guid [%ju:%ju] succeeded, provider %s.",
		    (uintmax_t)spa_guid(vd->vdev_spa),
		    (uintmax_t)vd->vdev_guid, cp->provider->name);
	} else {
		ZFS_LOG(1, "Search by guid [%ju:%ju] failed.",
		    (uintmax_t)spa_guid(vd->vdev_spa),
		    (uintmax_t)vd->vdev_guid);
	}

	return (cp);
}