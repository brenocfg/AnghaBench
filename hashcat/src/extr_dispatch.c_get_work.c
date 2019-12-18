#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ limit; } ;
typedef  TYPE_1__ user_options_t ;
typedef  scalar_t__ u64 ;
struct TYPE_12__ {scalar_t__ words_off; scalar_t__ words_base; int /*<<< orphan*/  mux_dispatcher; } ;
typedef  TYPE_2__ status_ctx_t ;
struct TYPE_13__ {scalar_t__ words_off; } ;
typedef  TYPE_3__ hc_device_param_t ;
struct TYPE_14__ {TYPE_1__* user_options; TYPE_2__* status_ctx; TYPE_5__* backend_ctx; } ;
typedef  TYPE_4__ hashcat_ctx_t ;
struct TYPE_15__ {scalar_t__ kernel_power_all; scalar_t__ kernel_power_final; } ;
typedef  TYPE_5__ backend_ctx_t ;

/* Variables and functions */
 scalar_t__ MIN (scalar_t__ const,scalar_t__ const) ; 
 scalar_t__ get_power (TYPE_5__*,TYPE_3__*) ; 
 int /*<<< orphan*/  hc_thread_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hc_thread_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_kernel_power_final (TYPE_4__*,scalar_t__ const) ; 

__attribute__((used)) static u64 get_work (hashcat_ctx_t *hashcat_ctx, hc_device_param_t *device_param, const u64 max)
{
  backend_ctx_t  *backend_ctx  = hashcat_ctx->backend_ctx;
  status_ctx_t   *status_ctx   = hashcat_ctx->status_ctx;
  user_options_t *user_options = hashcat_ctx->user_options;

  hc_thread_mutex_lock (status_ctx->mux_dispatcher);

  const u64 words_off  = status_ctx->words_off;
  const u64 words_base = (user_options->limit == 0) ? status_ctx->words_base : MIN (user_options->limit, status_ctx->words_base);

  device_param->words_off = words_off;

  const u64 kernel_power_all = backend_ctx->kernel_power_all;

  const u64 words_left = words_base - words_off;

  if (words_left < kernel_power_all)
  {
    if (backend_ctx->kernel_power_final == 0)
    {
      set_kernel_power_final (hashcat_ctx, words_left);
    }
  }

  const u64 kernel_power = get_power (backend_ctx, device_param);

  u64 work = MIN (words_left, kernel_power);

  work = MIN (work, max);

  status_ctx->words_off += work;

  hc_thread_mutex_unlock (status_ctx->mux_dispatcher);

  return work;
}