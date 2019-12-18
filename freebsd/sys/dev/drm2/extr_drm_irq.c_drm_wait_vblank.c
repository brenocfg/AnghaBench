#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int type; unsigned int sequence; } ;
struct TYPE_4__ {long sequence; int /*<<< orphan*/  tval_usec; int /*<<< orphan*/  tval_sec; } ;
union drm_wait_vblank {TYPE_2__ request; TYPE_1__ reply; } ;
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct drm_file {int dummy; } ;
struct drm_device {unsigned int num_crtcs; unsigned int* last_vblank_wait; int /*<<< orphan*/  vblank_time_lock; int /*<<< orphan*/ * _vblank_count; scalar_t__ irq_enabled; } ;
struct TYPE_6__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR5 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,int const,int,long) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,int) ; 
 int EINTR ; 
 int EINVAL ; 
 int ERESTART ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  KTR_DRM ; 
 int /*<<< orphan*/  PCATCH ; 
#define  _DRM_VBLANK_ABSOLUTE 129 
 unsigned int _DRM_VBLANK_EVENT ; 
 int _DRM_VBLANK_FLAGS_MASK ; 
 int _DRM_VBLANK_HIGH_CRTC_MASK ; 
 unsigned int _DRM_VBLANK_HIGH_CRTC_SHIFT ; 
 unsigned int _DRM_VBLANK_NEXTONMISS ; 
#define  _DRM_VBLANK_RELATIVE 128 
 unsigned int _DRM_VBLANK_SECONDARY ; 
 int _DRM_VBLANK_SIGNAL ; 
 int _DRM_VBLANK_TYPES_MASK ; 
 TYPE_3__* curproc ; 
 int drm_queue_vblank_event (struct drm_device*,unsigned int,union drm_wait_vblank*,struct drm_file*) ; 
 int drm_vblank_count (struct drm_device*,unsigned int) ; 
 long drm_vblank_count_and_time (struct drm_device*,unsigned int,struct timeval*) ; 
 int drm_vblank_get (struct drm_device*,unsigned int) ; 
 int /*<<< orphan*/  drm_vblank_put (struct drm_device*,unsigned int) ; 
 int hz ; 
 int msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int drm_wait_vblank(struct drm_device *dev, void *data,
		    struct drm_file *file_priv)
{
	union drm_wait_vblank *vblwait = data;
	int ret;
	unsigned int flags, seq, crtc, high_crtc;

	if (/*(!drm_dev_to_irq(dev)) || */(!dev->irq_enabled))
		return -EINVAL;

	if (vblwait->request.type & _DRM_VBLANK_SIGNAL)
		return -EINVAL;

	if (vblwait->request.type &
	    ~(_DRM_VBLANK_TYPES_MASK | _DRM_VBLANK_FLAGS_MASK |
	      _DRM_VBLANK_HIGH_CRTC_MASK)) {
		DRM_ERROR("Unsupported type value 0x%x, supported mask 0x%x\n",
			  vblwait->request.type,
			  (_DRM_VBLANK_TYPES_MASK | _DRM_VBLANK_FLAGS_MASK |
			   _DRM_VBLANK_HIGH_CRTC_MASK));
		return -EINVAL;
	}

	flags = vblwait->request.type & _DRM_VBLANK_FLAGS_MASK;
	high_crtc = (vblwait->request.type & _DRM_VBLANK_HIGH_CRTC_MASK);
	if (high_crtc)
		crtc = high_crtc >> _DRM_VBLANK_HIGH_CRTC_SHIFT;
	else
		crtc = flags & _DRM_VBLANK_SECONDARY ? 1 : 0;
	if (crtc >= dev->num_crtcs)
		return -EINVAL;

	ret = drm_vblank_get(dev, crtc);
	if (ret) {
		DRM_DEBUG("failed to acquire vblank counter, %d\n", ret);
		return ret;
	}
	seq = drm_vblank_count(dev, crtc);

	switch (vblwait->request.type & _DRM_VBLANK_TYPES_MASK) {
	case _DRM_VBLANK_RELATIVE:
		vblwait->request.sequence += seq;
		vblwait->request.type &= ~_DRM_VBLANK_RELATIVE;
	case _DRM_VBLANK_ABSOLUTE:
		break;
	default:
		ret = -EINVAL;
		goto done;
	}

	if (flags & _DRM_VBLANK_EVENT) {
		/* must hold on to the vblank ref until the event fires
		 * drm_vblank_put will be called asynchronously
		 */
		return drm_queue_vblank_event(dev, crtc, vblwait, file_priv);
	}

	if ((flags & _DRM_VBLANK_NEXTONMISS) &&
	    (seq - vblwait->request.sequence) <= (1<<23)) {
		vblwait->request.sequence = seq + 1;
	}

	DRM_DEBUG("waiting on vblank count %d, crtc %d\n",
		  vblwait->request.sequence, crtc);
	dev->last_vblank_wait[crtc] = vblwait->request.sequence;
	mtx_lock(&dev->vblank_time_lock);
	while (((drm_vblank_count(dev, crtc) - vblwait->request.sequence) >
	    (1 << 23)) && dev->irq_enabled) {
		/*
		 * The wakeups from the drm_irq_uninstall() and
		 * drm_vblank_off() may be lost there since vbl_lock
		 * is not held.  Then, the timeout will wake us; the 3
		 * seconds delay should not be a problem for
		 * application when crtc is disabled or irq
		 * uninstalled anyway.
		 */
		ret = -msleep(&dev->_vblank_count[crtc], &dev->vblank_time_lock,
		    PCATCH, "drmvbl", 3 * hz);
		if (ret == -ERESTART)
			ret = -ERESTARTSYS;
		if (ret != 0)
			break;
	}
	mtx_unlock(&dev->vblank_time_lock);
	if (ret != -EINTR) {
		struct timeval now;
		long reply_seq;

		reply_seq = drm_vblank_count_and_time(dev, crtc, &now);
		CTR5(KTR_DRM, "wait_vblank %d %d rt %x success %d %d",
		    curproc->p_pid, crtc, vblwait->request.type,
		    vblwait->request.sequence, reply_seq);

		vblwait->reply.sequence = reply_seq;
		vblwait->reply.tval_sec = now.tv_sec;
		vblwait->reply.tval_usec = now.tv_usec;

		DRM_DEBUG("returning %d to client\n",
			  vblwait->reply.sequence);
	} else {
		CTR5(KTR_DRM, "wait_vblank %d %d rt %x error %d %d",
		    curproc->p_pid, crtc, vblwait->request.type, ret,
		    vblwait->request.sequence);

		DRM_DEBUG("vblank wait interrupted by signal\n");
	}

done:
	drm_vblank_put(dev, crtc);
	return ret;
}