#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {int planes; int /*<<< orphan*/ * pitches; int /*<<< orphan*/ * pixels; } ;
typedef  TYPE_1__ SDL_VoutOverlay ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int AV_NUM_DATA_POINTERS ; 

__attribute__((used)) static void overlay_fill(SDL_VoutOverlay *overlay, AVFrame *frame, int planes)
{
    overlay->planes = planes;

    for (int i = 0; i < AV_NUM_DATA_POINTERS; ++i) {
        overlay->pixels[i] = frame->data[i];
        overlay->pitches[i] = frame->linesize[i];
    }
}