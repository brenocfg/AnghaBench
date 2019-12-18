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
struct TYPE_3__ {char* vdev_physpath; int /*<<< orphan*/  vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;
struct g_consumer {int dummy; } ;
typedef  int boolean_t ;

/* Variables and functions */
 int B_FALSE ; 
 int MAXPATHLEN ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SPA_ASYNC_CONFIG_UPDATE ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int g_io_getattr (char*,struct g_consumer*,int*,char*) ; 
 char* g_malloc (int,int) ; 
 int /*<<< orphan*/  g_topology_assert () ; 
 int /*<<< orphan*/  spa_async_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* spa_strdup (char*) ; 
 int /*<<< orphan*/  spa_strfree (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
vdev_geom_set_physpath(vdev_t *vd, struct g_consumer *cp,
		       boolean_t do_null_update)
{
	boolean_t needs_update = B_FALSE;
	char *physpath;
	int error, physpath_len;

	physpath_len = MAXPATHLEN;
	physpath = g_malloc(physpath_len, M_WAITOK|M_ZERO);
	error = g_io_getattr("GEOM::physpath", cp, &physpath_len, physpath);
	if (error == 0) {
		char *old_physpath;

		/* g_topology lock ensures that vdev has not been closed */
		g_topology_assert();
		old_physpath = vd->vdev_physpath;
		vd->vdev_physpath = spa_strdup(physpath);

		if (old_physpath != NULL) {
			needs_update = (strcmp(old_physpath,
						vd->vdev_physpath) != 0);
			spa_strfree(old_physpath);
		} else
			needs_update = do_null_update;
	}
	g_free(physpath);

	/*
	 * If the physical path changed, update the config.
	 * Only request an update for previously unset physpaths if
	 * requested by the caller.
	 */
	if (needs_update)
		spa_async_request(vd->vdev_spa, SPA_ASYNC_CONFIG_UPDATE);

}