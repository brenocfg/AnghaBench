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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct vqueue_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vq_relchain_prepare (struct vqueue_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vq_relchain_publish (struct vqueue_info*) ; 

void
vq_relchain(struct vqueue_info *vq, uint16_t idx, uint32_t iolen)
{
	vq_relchain_prepare(vq, idx, iolen);
	vq_relchain_publish(vq);
}