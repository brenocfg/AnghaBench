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
struct drm_unique {scalar_t__ unique_len; int /*<<< orphan*/  unique; } ;
struct drm_master {scalar_t__ unique_len; int /*<<< orphan*/  unique; } ;
struct drm_file {struct drm_master* master; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int drm_getunique(struct drm_device *dev, void *data,
		  struct drm_file *file_priv)
{
	struct drm_unique *u = data;
	struct drm_master *master = file_priv->master;

	if (u->unique_len >= master->unique_len) {
		if (copy_to_user(u->unique, master->unique, master->unique_len))
			return -EFAULT;
	}
	u->unique_len = master->unique_len;

	return 0;
}