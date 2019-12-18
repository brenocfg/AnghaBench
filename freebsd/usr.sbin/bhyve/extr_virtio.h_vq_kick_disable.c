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
struct vqueue_info {TYPE_1__* vq_used; } ;
struct TYPE_2__ {int /*<<< orphan*/  vu_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  VRING_USED_F_NO_NOTIFY ; 

__attribute__((used)) static inline void
vq_kick_disable(struct vqueue_info *vq)
{

	vq->vq_used->vu_flags |= VRING_USED_F_NO_NOTIFY;
}