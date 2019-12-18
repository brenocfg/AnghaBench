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
struct ttm_buffer_object {TYPE_1__* glob; } ;
struct TYPE_2__ {int /*<<< orphan*/  lru_lock; } ;

/* Variables and functions */
 int EINTR ; 
 int ERESTART ; 
 int ERESTARTSYS ; 
 int PCATCH ; 
 int msleep (struct ttm_buffer_object*,int /*<<< orphan*/ *,int,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ttm_bo_is_reserved (struct ttm_buffer_object*) ; 

__attribute__((used)) static int
ttm_bo_wait_unreserved_locked(struct ttm_buffer_object *bo, bool interruptible)
{
	const char *wmsg;
	int flags, ret;

	ret = 0;
	if (interruptible) {
		flags = PCATCH;
		wmsg = "ttbowi";
	} else {
		flags = 0;
		wmsg = "ttbowu";
	}
	while (ttm_bo_is_reserved(bo)) {
		ret = -msleep(bo, &bo->glob->lru_lock, flags, wmsg, 0);
		if (ret == -EINTR || ret == -ERESTART)
			ret = -ERESTARTSYS;
		if (ret != 0)
			break;
	}
	return (ret);
}