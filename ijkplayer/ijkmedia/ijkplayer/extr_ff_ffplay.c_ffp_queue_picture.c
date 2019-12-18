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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  FFPlayer ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int queue_picture (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double,double,int /*<<< orphan*/ ,int) ; 

int ffp_queue_picture(FFPlayer *ffp, AVFrame *src_frame, double pts, double duration, int64_t pos, int serial)
{
    return queue_picture(ffp, src_frame, pts, duration, pos, serial);
}