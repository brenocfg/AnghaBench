#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_17__ {int /*<<< orphan*/  bytes_left; int /*<<< orphan*/  body_obj; } ;
typedef  TYPE_6__ h2o_mruby_sender_t ;
struct TYPE_18__ {TYPE_5__* req; TYPE_2__* ctx; } ;
typedef  TYPE_7__ h2o_mruby_generator_t ;
struct TYPE_15__ {int /*<<< orphan*/  content_length; } ;
struct TYPE_14__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_16__ {TYPE_4__ res; TYPE_3__ method; int /*<<< orphan*/  pool; } ;
struct TYPE_13__ {TYPE_1__* shared; } ;
struct TYPE_12__ {int /*<<< orphan*/  mrb; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 TYPE_6__* h2o_mem_alloc_pool_aligned (int /*<<< orphan*/ *,size_t,size_t) ; 
 scalar_t__ h2o_memis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mrb_gc_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_p (int /*<<< orphan*/ ) ; 

h2o_mruby_sender_t *h2o_mruby_sender_create(h2o_mruby_generator_t *generator, mrb_value body, size_t alignment, size_t sz)
{
    h2o_mruby_sender_t *sender = h2o_mem_alloc_pool_aligned(&generator->req->pool, alignment, sz);
    memset(sender, 0, sz);
    sender->body_obj = body;
    if (!mrb_nil_p(body))
        mrb_gc_register(generator->ctx->shared->mrb, body);
    sender->bytes_left = h2o_memis(generator->req->method.base, generator->req->method.len, H2O_STRLIT("HEAD"))
                             ? 0
                             : generator->req->res.content_length;
    return sender;
}