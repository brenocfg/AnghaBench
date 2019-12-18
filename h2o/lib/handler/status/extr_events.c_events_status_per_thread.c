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
struct st_events_status_ctx_t {int /*<<< orphan*/  mutex; int /*<<< orphan*/  h2_write_closed; int /*<<< orphan*/  h2_read_closed; int /*<<< orphan*/ * h2_protocol_level_errors; int /*<<< orphan*/  ssl_errors; int /*<<< orphan*/ * emitted_status_errors; } ;
struct TYPE_7__ {scalar_t__ write_closed; scalar_t__ read_closed; scalar_t__* protocol_level_errors; } ;
struct TYPE_8__ {TYPE_2__ events; } ;
struct TYPE_6__ {scalar_t__ errors; } ;
struct TYPE_9__ {TYPE_3__ http2; TYPE_1__ ssl; scalar_t__* emitted_error_status; } ;
typedef  TYPE_4__ h2o_context_t ;

/* Variables and functions */
 size_t H2O_HTTP2_ERROR_MAX ; 
 size_t H2O_STATUS_ERROR_MAX ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void events_status_per_thread(void *priv, h2o_context_t *ctx)
{
    size_t i;
    struct st_events_status_ctx_t *esc = priv;

    pthread_mutex_lock(&esc->mutex);

    for (i = 0; i < H2O_STATUS_ERROR_MAX; i++) {
        esc->emitted_status_errors[i] += ctx->emitted_error_status[i];
    }
    esc->ssl_errors += ctx->ssl.errors;
    for (i = 0; i < H2O_HTTP2_ERROR_MAX; i++) {
        esc->h2_protocol_level_errors[i] += ctx->http2.events.protocol_level_errors[i];
    }
    esc->h2_read_closed += ctx->http2.events.read_closed;
    esc->h2_write_closed += ctx->http2.events.write_closed;

    pthread_mutex_unlock(&esc->mutex);
}