#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sub; int /*<<< orphan*/  bmp; int /*<<< orphan*/  frame; } ;
typedef  TYPE_1__ Frame ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_VoutUnrefYUVOverlay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avsubtitle_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void frame_queue_unref_item(Frame *vp)
{
    av_frame_unref(vp->frame);
    SDL_VoutUnrefYUVOverlay(vp->bmp);
    avsubtitle_free(&vp->sub);
}