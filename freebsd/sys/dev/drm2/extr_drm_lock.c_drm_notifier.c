#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct drm_sigdata {scalar_t__ context; TYPE_1__* lock; } ;
struct TYPE_2__ {unsigned int lock; } ;

/* Variables and functions */
 scalar_t__ _DRM_LOCKING_CONTEXT (unsigned int) ; 
 unsigned int _DRM_LOCK_CONT ; 
 int /*<<< orphan*/  _DRM_LOCK_IS_HELD (unsigned int) ; 
 unsigned int cmpxchg (unsigned int*,unsigned int,unsigned int) ; 

__attribute__((used)) static int drm_notifier(void *priv)
{
	struct drm_sigdata *s = (struct drm_sigdata *) priv;
	unsigned int old, new, prev;

	/* Allow signal delivery if lock isn't held */
	if (!s->lock || !_DRM_LOCK_IS_HELD(s->lock->lock)
	    || _DRM_LOCKING_CONTEXT(s->lock->lock) != s->context)
		return 1;

	/* Otherwise, set flag to force call to
	   drmUnlock */
	do {
		old = s->lock->lock;
		new = old | _DRM_LOCK_CONT;
		prev = cmpxchg(&s->lock->lock, old, new);
	} while (prev != old);
	return 0;
}