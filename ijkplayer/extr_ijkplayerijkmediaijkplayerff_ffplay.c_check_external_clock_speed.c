#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {double speed; } ;
struct TYPE_7__ {scalar_t__ nb_packets; } ;
struct TYPE_6__ {scalar_t__ nb_packets; } ;
struct TYPE_8__ {scalar_t__ video_stream; scalar_t__ audio_stream; TYPE_4__ extclk; TYPE_2__ audioq; TYPE_1__ videoq; } ;
typedef  TYPE_3__ VideoState ;

/* Variables and functions */
 scalar_t__ EXTERNAL_CLOCK_MAX_FRAMES ; 
 scalar_t__ EXTERNAL_CLOCK_MIN_FRAMES ; 
 int /*<<< orphan*/  EXTERNAL_CLOCK_SPEED_MAX ; 
 int /*<<< orphan*/  EXTERNAL_CLOCK_SPEED_MIN ; 
 double EXTERNAL_CLOCK_SPEED_STEP ; 
 double FFMAX (int /*<<< orphan*/ ,double) ; 
 double FFMIN (int /*<<< orphan*/ ,double) ; 
 double fabs (double) ; 
 int /*<<< orphan*/  set_clock_speed (TYPE_4__*,double) ; 

__attribute__((used)) static void check_external_clock_speed(VideoState *is) {
   if ((is->video_stream >= 0 && is->videoq.nb_packets <= EXTERNAL_CLOCK_MIN_FRAMES) ||
       (is->audio_stream >= 0 && is->audioq.nb_packets <= EXTERNAL_CLOCK_MIN_FRAMES)) {
       set_clock_speed(&is->extclk, FFMAX(EXTERNAL_CLOCK_SPEED_MIN, is->extclk.speed - EXTERNAL_CLOCK_SPEED_STEP));
   } else if ((is->video_stream < 0 || is->videoq.nb_packets > EXTERNAL_CLOCK_MAX_FRAMES) &&
              (is->audio_stream < 0 || is->audioq.nb_packets > EXTERNAL_CLOCK_MAX_FRAMES)) {
       set_clock_speed(&is->extclk, FFMIN(EXTERNAL_CLOCK_SPEED_MAX, is->extclk.speed + EXTERNAL_CLOCK_SPEED_STEP));
   } else {
       double speed = is->extclk.speed;
       if (speed != 1.0)
           set_clock_speed(&is->extclk, speed + EXTERNAL_CLOCK_SPEED_STEP * (1.0 - speed) / fabs(1.0 - speed));
   }
}