#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yoml_t ;
struct st_core_configurator_t {TYPE_7__* vars; } ;
typedef  int /*<<< orphan*/  h2o_configurator_t ;
struct TYPE_17__ {TYPE_5__* pathconf; TYPE_2__* hostconf; } ;
typedef  TYPE_8__ h2o_configurator_context_t ;
struct TYPE_15__ {int /*<<< orphan*/  emit_request_errors; } ;
struct TYPE_12__ {int /*<<< orphan*/  casper; int /*<<< orphan*/  allow_cross_origin_push; int /*<<< orphan*/  push_preload; int /*<<< orphan*/  reprioritize_blocking_assets; } ;
struct TYPE_16__ {TYPE_6__ error_log; TYPE_3__ http2; } ;
struct TYPE_13__ {int /*<<< orphan*/  emit_request_errors; } ;
struct TYPE_14__ {TYPE_4__ error_log; } ;
struct TYPE_10__ {int /*<<< orphan*/  casper; int /*<<< orphan*/  allow_cross_origin_push; int /*<<< orphan*/  push_preload; int /*<<< orphan*/  reprioritize_blocking_assets; } ;
struct TYPE_11__ {TYPE_1__ http2; } ;

/* Variables and functions */

__attribute__((used)) static int on_core_exit(h2o_configurator_t *_self, h2o_configurator_context_t *ctx, yoml_t *node)
{
    struct st_core_configurator_t *self = (void *)_self;

    if (ctx->hostconf != NULL && ctx->pathconf == NULL) {
        /* exitting from host-level configuration */
        ctx->hostconf->http2.reprioritize_blocking_assets = self->vars->http2.reprioritize_blocking_assets;
        ctx->hostconf->http2.push_preload = self->vars->http2.push_preload;
        ctx->hostconf->http2.allow_cross_origin_push = self->vars->http2.allow_cross_origin_push;
        ctx->hostconf->http2.casper = self->vars->http2.casper;
    } else if (ctx->pathconf != NULL) {
        /* exitting from path or extension-level configuration */
        ctx->pathconf->error_log.emit_request_errors = self->vars->error_log.emit_request_errors;
    }

    --self->vars;
    return 0;
}