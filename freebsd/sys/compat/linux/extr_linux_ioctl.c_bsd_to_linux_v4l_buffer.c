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
struct video_buffer {int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  depth; int /*<<< orphan*/  width; int /*<<< orphan*/  height; int /*<<< orphan*/  base; } ;
struct l_video_buffer {int /*<<< orphan*/  bytesperline; int /*<<< orphan*/  depth; int /*<<< orphan*/  width; int /*<<< orphan*/  height; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTROUT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bsd_to_linux_v4l_buffer(struct video_buffer *vb, struct l_video_buffer *lvb)
{
	lvb->base = PTROUT(vb->base);	/* possible pointer size conversion */
	lvb->height = vb->height;
	lvb->width = vb->width;
	lvb->depth = vb->depth;
	lvb->bytesperline = vb->bytesperline;
	return (0);
}