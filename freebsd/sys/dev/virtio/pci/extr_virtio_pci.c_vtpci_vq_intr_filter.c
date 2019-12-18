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
struct virtqueue {int dummy; } ;

/* Variables and functions */
 int FILTER_SCHEDULE_THREAD ; 
 int FILTER_STRAY ; 
 int virtqueue_intr_filter (struct virtqueue*) ; 

__attribute__((used)) static int
vtpci_vq_intr_filter(void *xvq)
{
	struct virtqueue *vq;
	int rc;

	vq = xvq;
	rc = virtqueue_intr_filter(vq);

	return (rc ? FILTER_SCHEDULE_THREAD : FILTER_STRAY);
}