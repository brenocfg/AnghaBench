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
typedef  int /*<<< orphan*/  vm_paddr_t ;
struct virtqueue {int /*<<< orphan*/  vq_ring_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  vtophys (int /*<<< orphan*/ ) ; 

vm_paddr_t
virtqueue_paddr(struct virtqueue *vq)
{

	return (vtophys(vq->vq_ring_mem));
}