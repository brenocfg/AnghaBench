#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {double engine_frame_period_msec; } ;
typedef  TYPE_1__ GameContext ;

/* Variables and functions */
 double kEngineTimePerExternalTime ; 

__attribute__((used)) static int dmlab_fps(void* context) {
  GameContext* gc = context;
  if (gc->engine_frame_period_msec > 0) {
    return (1000.0 * kEngineTimePerExternalTime) / gc->engine_frame_period_msec;
  } else {
    return 0;
  }
}