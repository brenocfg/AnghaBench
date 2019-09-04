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
struct TYPE_5__ {scalar_t__ video_st; } ;
typedef  TYPE_1__ VideoState ;
struct TYPE_6__ {TYPE_1__* is; } ;
typedef  TYPE_2__ FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  video_image_display2 (TYPE_2__*) ; 

__attribute__((used)) static void video_display2(FFPlayer *ffp)
{
    VideoState *is = ffp->is;
    if (is->video_st)
        video_image_display2(ffp);
}