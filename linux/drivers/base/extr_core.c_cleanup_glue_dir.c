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
struct kobject {int /*<<< orphan*/  kref; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdp_mutex ; 
 int /*<<< orphan*/  kobject_del (struct kobject*) ; 
 int /*<<< orphan*/  kobject_has_children (struct kobject*) ; 
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 
 unsigned int kref_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  live_in_glue_dir (struct kobject*,struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cleanup_glue_dir(struct device *dev, struct kobject *glue_dir)
{
	unsigned int ref;

	/* see if we live in a "glue" directory */
	if (!live_in_glue_dir(glue_dir, dev))
		return;

	mutex_lock(&gdp_mutex);
	/**
	 * There is a race condition between removing glue directory
	 * and adding a new device under the glue directory.
	 *
	 * CPU1:                                         CPU2:
	 *
	 * device_add()
	 *   get_device_parent()
	 *     class_dir_create_and_add()
	 *       kobject_add_internal()
	 *         create_dir()    // create glue_dir
	 *
	 *                                               device_add()
	 *                                                 get_device_parent()
	 *                                                   kobject_get() // get glue_dir
	 *
	 * device_del()
	 *   cleanup_glue_dir()
	 *     kobject_del(glue_dir)
	 *
	 *                                               kobject_add()
	 *                                                 kobject_add_internal()
	 *                                                   create_dir() // in glue_dir
	 *                                                     sysfs_create_dir_ns()
	 *                                                       kernfs_create_dir_ns(sd)
	 *
	 *       sysfs_remove_dir() // glue_dir->sd=NULL
	 *       sysfs_put()        // free glue_dir->sd
	 *
	 *                                                         // sd is freed
	 *                                                         kernfs_new_node(sd)
	 *                                                           kernfs_get(glue_dir)
	 *                                                           kernfs_add_one()
	 *                                                           kernfs_put()
	 *
	 * Before CPU1 remove last child device under glue dir, if CPU2 add
	 * a new device under glue dir, the glue_dir kobject reference count
	 * will be increase to 2 in kobject_get(k). And CPU2 has been called
	 * kernfs_create_dir_ns(). Meanwhile, CPU1 call sysfs_remove_dir()
	 * and sysfs_put(). This result in glue_dir->sd is freed.
	 *
	 * Then the CPU2 will see a stale "empty" but still potentially used
	 * glue dir around in kernfs_new_node().
	 *
	 * In order to avoid this happening, we also should make sure that
	 * kernfs_node for glue_dir is released in CPU1 only when refcount
	 * for glue_dir kobj is 1.
	 */
	ref = kref_read(&glue_dir->kref);
	if (!kobject_has_children(glue_dir) && !--ref)
		kobject_del(glue_dir);
	kobject_put(glue_dir);
	mutex_unlock(&gdp_mutex);
}