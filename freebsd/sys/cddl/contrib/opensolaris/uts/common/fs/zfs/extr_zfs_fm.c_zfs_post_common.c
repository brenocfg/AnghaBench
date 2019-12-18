#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  vdev_guid; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  class ;

/* Variables and functions */
 int /*<<< orphan*/  EVCH_SLEEP ; 
 int /*<<< orphan*/  FM_CLASS ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_POOL_GUID ; 
 int /*<<< orphan*/  FM_EREPORT_PAYLOAD_ZFS_VDEV_GUID ; 
 int /*<<< orphan*/  FM_NVA_FREE ; 
 char* FM_RSRC_RESOURCE ; 
 int /*<<< orphan*/  FM_RSRC_VERSION ; 
 int /*<<< orphan*/  FM_VERSION ; 
 scalar_t__ SPA_LOAD_TRYIMPORT ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 char* ZFS_ERROR_CLASS ; 
 int /*<<< orphan*/  fm_ereport_post (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fm_nvlist_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fm_nvlist_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_add_uint8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  spa_guid (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_load_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zfs_post_common(spa_t *spa, vdev_t *vd, const char *name)
{
#ifdef _KERNEL
	nvlist_t *resource;
	char class[64];

	if (spa_load_state(spa) == SPA_LOAD_TRYIMPORT)
		return;

	if ((resource = fm_nvlist_create(NULL)) == NULL)
		return;

	(void) snprintf(class, sizeof (class), "%s.%s.%s", FM_RSRC_RESOURCE,
	    ZFS_ERROR_CLASS, name);
	VERIFY(nvlist_add_uint8(resource, FM_VERSION, FM_RSRC_VERSION) == 0);
	VERIFY(nvlist_add_string(resource, FM_CLASS, class) == 0);
	VERIFY(nvlist_add_uint64(resource,
	    FM_EREPORT_PAYLOAD_ZFS_POOL_GUID, spa_guid(spa)) == 0);
	if (vd)
		VERIFY(nvlist_add_uint64(resource,
		    FM_EREPORT_PAYLOAD_ZFS_VDEV_GUID, vd->vdev_guid) == 0);

	fm_ereport_post(resource, EVCH_SLEEP);

	fm_nvlist_destroy(resource, FM_NVA_FREE);
#endif
}