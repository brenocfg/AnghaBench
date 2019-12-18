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
struct TYPE_5__ {int /*<<< orphan*/  hashcat_status_final; int /*<<< orphan*/  mux_hwmon; int /*<<< orphan*/  mux_display; int /*<<< orphan*/  mux_counter; int /*<<< orphan*/  mux_dispatcher; } ;
typedef  TYPE_1__ status_ctx_t ;
struct TYPE_6__ {TYPE_1__* status_ctx; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  hc_thread_mutex_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hcfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void status_ctx_destroy (hashcat_ctx_t *hashcat_ctx)
{
  status_ctx_t *status_ctx = hashcat_ctx->status_ctx;

  hc_thread_mutex_delete (status_ctx->mux_dispatcher);
  hc_thread_mutex_delete (status_ctx->mux_counter);
  hc_thread_mutex_delete (status_ctx->mux_display);
  hc_thread_mutex_delete (status_ctx->mux_hwmon);

  hcfree (status_ctx->hashcat_status_final);

  memset (status_ctx, 0, sizeof (status_ctx_t));
}