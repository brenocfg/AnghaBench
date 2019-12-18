#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ devices_status; int run_main_level1; int run_main_level2; int run_main_level3; int run_thread_level1; int run_thread_level2; } ;
typedef  TYPE_1__ status_ctx_t ;
struct TYPE_5__ {TYPE_1__* status_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 scalar_t__ STATUS_PAUSED ; 
 scalar_t__ STATUS_QUIT ; 
 scalar_t__ STATUS_RUNNING ; 

int myquit (hashcat_ctx_t *hashcat_ctx)
{
  status_ctx_t *status_ctx = hashcat_ctx->status_ctx;

  if (status_ctx->devices_status != STATUS_RUNNING && status_ctx->devices_status != STATUS_PAUSED) return -1;

  status_ctx->devices_status = STATUS_QUIT;

  status_ctx->run_main_level1   = false;
  status_ctx->run_main_level2   = false;
  status_ctx->run_main_level3   = false;
  status_ctx->run_thread_level1 = false;
  status_ctx->run_thread_level2 = false;

  return 0;
}