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
 int /*<<< orphan*/  PTROUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct l_video_window*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bsd_to_linux_v4l_window(struct video_window *vw, struct l_video_window *lvw)
{
	memset(lvw, 0, sizeof(*lvw));

	lvw->x = vw->x;
	lvw->y = vw->y;
	lvw->width = vw->width;
	lvw->height = vw->height;
	lvw->chromakey = vw->chromakey;
	lvw->flags = vw->flags;
	lvw->clips = PTROUT(vw->clips);	/* possible pointer size conversion */
	lvw->clipcount = vw->clipcount;
	return (0);
}