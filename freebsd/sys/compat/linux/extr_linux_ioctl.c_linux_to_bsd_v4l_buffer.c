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
 int /*<<< orphan*/  PTRIN (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
linux_to_bsd_v4l_buffer(struct l_video_buffer *lvb, struct video_buffer *vb)
{
	vb->base = PTRIN(lvb->base);	/* possible pointer size conversion */
	vb->height = lvb->height;
	vb->width = lvb->width;
	vb->depth = lvb->depth;
	vb->bytesperline = lvb->bytesperline;
	return (0);
}