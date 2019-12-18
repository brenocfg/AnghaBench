#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gmesh {int dummy; } ;
struct gclass {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  HRDBG (char*,...) ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  assert (int) ; 
 struct gclass* find_class (struct gmesh*,char*) ; 
 int /*<<< orphan*/  geom_deletetree (struct gmesh*) ; 
 int geom_gettree (struct gmesh*) ; 
 int /*<<< orphan*/  get_bsd_sun (struct gclass*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  get_mbr (struct gclass*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

void
partition_tbl_handle_disk(int32_t ds_index, const char *disk_dev_name)
{
	struct gmesh mesh;	/* GEOM userland tree */
	struct gclass *classp;
	int error;

	assert(disk_dev_name != NULL);
	assert(ds_index > 0);

	HRDBG("===> getting partitions for %s <===", disk_dev_name);

	/* try to construct the GEOM tree */
	if ((error = geom_gettree(&mesh)) != 0) {
		syslog(LOG_WARNING, "cannot get GEOM tree: %m");
		return;
	}

	/*
	 * First try the GEOM "MBR" class.
	 * This is needed for non-BSD slices (aka partitions)
	 * on PC architectures.
	 */
	if ((classp = find_class(&mesh, "MBR")) != NULL) {
		get_mbr(classp, ds_index, disk_dev_name);
	} else {
		HRDBG("cannot find \"MBR\" geom class");
	}

	/*
	 * Get the "BSD" GEOM class.
	 * Here we'll find all the info needed about the BSD slices.
	 */
	if ((classp = find_class(&mesh, "BSD")) != NULL) {
		get_bsd_sun(classp, ds_index, disk_dev_name);
	} else {
		/* no problem on sparc64 */
		HRDBG("cannot find \"BSD\" geom class");
	}

	/*
	 * Get the "SUN" GEOM class.
	 * Here we'll find all the info needed about the BSD slices.
	 */
	if ((classp = find_class(&mesh, "SUN")) != NULL) {
		get_bsd_sun(classp, ds_index, disk_dev_name);
	} else {
		/* no problem on i386 */
		HRDBG("cannot find \"SUN\" geom class");
	}

	geom_deletetree(&mesh);
}