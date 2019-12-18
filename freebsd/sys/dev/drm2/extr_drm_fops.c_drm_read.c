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
struct uio {int dummy; } ;
struct drm_pending_event {int /*<<< orphan*/  (* destroy ) (struct drm_pending_event*) ;TYPE_1__* event; } ;
struct drm_file {int /*<<< orphan*/  event_space; int /*<<< orphan*/  event_list; } ;
struct drm_device {int /*<<< orphan*/  event_lock; } ;
struct cdev {int dummy; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  p_pid; } ;
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  KTR_DRM ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  PCATCH ; 
 TYPE_2__* curproc ; 
 scalar_t__ devfs_get_cdevpriv (void**) ; 
 scalar_t__ drm_dequeue_event (struct drm_file*,struct uio*,struct drm_pending_event**) ; 
 struct drm_device* drm_get_device_from_kdev (struct cdev*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_pending_event*) ; 
 scalar_t__ uiomove (TYPE_1__*,int /*<<< orphan*/ ,struct uio*) ; 

int
drm_read(struct cdev *kdev, struct uio *uio, int ioflag)
{
	struct drm_file *file_priv;
	struct drm_device *dev;
	struct drm_pending_event *e;
	ssize_t error;

	error = devfs_get_cdevpriv((void **)&file_priv);
	if (error != 0) {
		DRM_ERROR("can't find authenticator\n");
		return (EINVAL);
	}

	dev = drm_get_device_from_kdev(kdev);
	mtx_lock(&dev->event_lock);
	while (list_empty(&file_priv->event_list)) {
		if ((ioflag & O_NONBLOCK) != 0) {
			error = EAGAIN;
			goto out;
		}
		error = msleep(&file_priv->event_space, &dev->event_lock,
	           PCATCH, "drmrea", 0);
	       if (error != 0)
		       goto out;
	}

	while (drm_dequeue_event(file_priv, uio, &e)) {
		mtx_unlock(&dev->event_lock);
		error = uiomove(e->event, e->event->length, uio);
		CTR3(KTR_DRM, "drm_event_dequeued %d %d %d", curproc->p_pid,
		    e->event->type, e->event->length);

		e->destroy(e);
		if (error != 0)
			return (error);
		mtx_lock(&dev->event_lock);
	}

out:
	mtx_unlock(&dev->event_lock);
	return (error);
}