#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ v_state; int (* v_read ) (TYPE_1__*,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ ,size_t) ;int /*<<< orphan*/  v_children; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int EIO ; 
 TYPE_1__* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ VDEV_STATE_HEALTHY ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
vdev_replacing_read(vdev_t *vdev, const blkptr_t *bp, void *buf,
    off_t offset, size_t bytes)
{
	vdev_t *kid;

	/*
	 * Here we should have two kids:
	 * First one which is the one we are replacing and we can trust
	 * only this one to have valid data, but it might not be present.
	 * Second one is that one we are replacing with. It is most likely
	 * healthy, but we can't trust it has needed data, so we won't use it.
	 */
	kid = STAILQ_FIRST(&vdev->v_children);
	if (kid == NULL)
		return (EIO);
	if (kid->v_state != VDEV_STATE_HEALTHY)
		return (EIO);
	return (kid->v_read(kid, bp, buf, offset, bytes));
}