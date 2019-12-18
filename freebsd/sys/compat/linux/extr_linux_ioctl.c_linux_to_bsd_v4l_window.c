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
struct video_window {int /*<<< orphan*/  clipcount; int /*<<< orphan*/  clips; int /*<<< orphan*/  flags; int /*<<< orphan*/  chromakey; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct l_video_window {int /*<<< orphan*/  clipcount; int /*<<< orphan*/  clips; int /*<<< orphan*/  flags; int /*<<< orphan*/  chromakey; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTRIN (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
linux_to_bsd_v4l_window(struct l_video_window *lvw, struct video_window *vw)
{
	vw->x = lvw->x;
	vw->y = lvw->y;
	vw->width = lvw->width;
	vw->height = lvw->height;
	vw->chromakey = lvw->chromakey;
	vw->flags = lvw->flags;
	vw->clips = PTRIN(lvw->clips);	/* possible pointer size conversion */
	vw->clipcount = lvw->clipcount;
	return (0);
}