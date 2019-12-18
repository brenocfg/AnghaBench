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
struct thread {int dummy; } ;
struct drm_file {int /*<<< orphan*/  event_poll; int /*<<< orphan*/  event_list; } ;
struct drm_device {int /*<<< orphan*/  event_lock; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CTR1 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  KTR_DRM ; 
 int POLLIN ; 
 int POLLRDNORM ; 
 int devfs_get_cdevpriv (void**) ; 
 struct drm_device* drm_get_device_from_kdev (struct cdev*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

int
drm_poll(struct cdev *kdev, int events, struct thread *td)
{
	struct drm_file *file_priv;
	struct drm_device *dev;
	int error, revents;

	error = devfs_get_cdevpriv((void **)&file_priv);
	if (error != 0) {
		DRM_ERROR("can't find authenticator\n");
		return (EINVAL);
	}

	dev = drm_get_device_from_kdev(kdev);

	revents = 0;
	mtx_lock(&dev->event_lock);
	if ((events & (POLLIN | POLLRDNORM)) != 0) {
		if (list_empty(&file_priv->event_list)) {
			CTR0(KTR_DRM, "drm_poll empty list");
			selrecord(td, &file_priv->event_poll);
		} else {
			revents |= events & (POLLIN | POLLRDNORM);
			CTR1(KTR_DRM, "drm_poll revents %x", revents);
		}
	}
	mtx_unlock(&dev->event_lock);
	return (revents);
}