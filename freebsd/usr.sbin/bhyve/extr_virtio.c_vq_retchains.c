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
typedef  scalar_t__ uint16_t ;
struct vqueue_info {int /*<<< orphan*/  vq_last_avail; } ;

/* Variables and functions */

void
vq_retchains(struct vqueue_info *vq, uint16_t n_chains)
{

	vq->vq_last_avail -= n_chains;
}