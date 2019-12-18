#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ runtime; } ;
typedef  TYPE_1__ user_options_t ;
typedef  scalar_t__ time_t ;
struct TYPE_6__ {double msec_paused; scalar_t__ devices_status; scalar_t__ runtime_start; int /*<<< orphan*/  timer_paused; } ;
typedef  TYPE_2__ status_ctx_t ;
struct TYPE_7__ {TYPE_1__* user_options; TYPE_2__* status_ctx; } ;
typedef  TYPE_3__ hashcat_ctx_t ;

/* Variables and functions */
 scalar_t__ STATUS_PAUSED ; 
 double hc_timer_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 

int get_runtime_left (const hashcat_ctx_t *hashcat_ctx)
{
  const status_ctx_t   *status_ctx   = hashcat_ctx->status_ctx;
  const user_options_t *user_options = hashcat_ctx->user_options;

  double msec_paused = status_ctx->msec_paused;

  if (status_ctx->devices_status == STATUS_PAUSED)
  {
    double msec_paused_tmp = hc_timer_get (status_ctx->timer_paused);

    msec_paused += msec_paused_tmp;
  }

  time_t runtime_cur;

  time (&runtime_cur);

  const int runtime_left = (int) (status_ctx->runtime_start
                                + user_options->runtime
                                + (msec_paused / 1000)
                                - runtime_cur);

  return runtime_left;
}