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
struct api_info {unsigned long major; unsigned long minor; scalar_t__ refcnt; } ;

/* Variables and functions */
 int EINVAL ; 
 struct api_info* __get_info (unsigned long) ; 
 int /*<<< orphan*/  hvapi_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int sun4v_hvapi_get(unsigned long group,
		    unsigned long *major,
		    unsigned long *minor)
{
	struct api_info *p;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&hvapi_lock, flags);
	ret = -EINVAL;
	p = __get_info(group);
	if (p && p->refcnt) {
		*major = p->major;
		*minor = p->minor;
		ret = 0;
	}
	spin_unlock_irqrestore(&hvapi_lock, flags);

	return ret;
}