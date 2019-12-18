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
struct TYPE_3__ {int size; int rindex_shown; } ;
typedef  TYPE_1__ FrameQueue ;

/* Variables and functions */

__attribute__((used)) static int frame_queue_nb_remaining(FrameQueue *f)
{
    return f->size - f->rindex_shown;
}