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
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 void* virtqueue_drain (struct virtqueue*,int*) ; 

__attribute__((used)) static void
vtcon_port_drain_bufs(struct virtqueue *vq)
{
	void *buf;
	int last;

	last = 0;

	while ((buf = virtqueue_drain(vq, &last)) != NULL)
		free(buf, M_DEVBUF);
}