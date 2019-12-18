#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ devices_status; int checkpoint_shutdown; int run_main_level1; int run_main_level2; int run_main_level3; int run_thread_level1; int run_thread_level2; } ;
typedef  TYPE_1__ status_ctx_t ;
struct TYPE_7__ {int enabled; } ;
typedef  TYPE_2__ restore_ctx_t ;
struct TYPE_8__ {TYPE_2__* restore_ctx; TYPE_1__* status_ctx; } ;
typedef  TYPE_3__ hashcat_ctx_t ;

/* Variables and functions */
 scalar_t__ STATUS_RUNNING ; 
 int /*<<< orphan*/  event_log_warning (TYPE_3__*,char*) ; 

int stop_at_checkpoint (hashcat_ctx_t *hashcat_ctx)
{
  status_ctx_t  *status_ctx  = hashcat_ctx->status_ctx;

  if (status_ctx->devices_status != STATUS_RUNNING) return -1;

  // this feature only makes sense if --restore-disable was not specified

  restore_ctx_t *restore_ctx = hashcat_ctx->restore_ctx;

  if (restore_ctx->enabled == false)
  {
    event_log_warning (hashcat_ctx, "This feature is disabled when --restore-disable is specified.");

    return -1;
  }

  // Enable or Disable

  if (status_ctx->checkpoint_shutdown == false)
  {
    status_ctx->checkpoint_shutdown = true;

    status_ctx->run_main_level1   = false;
    status_ctx->run_main_level2   = false;
    status_ctx->run_main_level3   = false;
    status_ctx->run_thread_level1 = false;
    status_ctx->run_thread_level2 = true;
  }
  else
  {
    status_ctx->checkpoint_shutdown = false;

    status_ctx->run_main_level1   = true;
    status_ctx->run_main_level2   = true;
    status_ctx->run_main_level3   = true;
    status_ctx->run_thread_level1 = true;
    status_ctx->run_thread_level2 = true;
  }

  return 0;
}