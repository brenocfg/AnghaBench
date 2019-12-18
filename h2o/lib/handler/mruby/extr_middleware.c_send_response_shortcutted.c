#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;

/* Type definitions */
struct TYPE_20__ {int size; TYPE_9__* entries; } ;
struct TYPE_21__ {TYPE_2__ headers; int /*<<< orphan*/  mime_attr; int /*<<< orphan*/  content_length; int /*<<< orphan*/  reason; int /*<<< orphan*/  status; } ;
struct TYPE_22__ {TYPE_3__ res; } ;
struct TYPE_19__ {TYPE_8__* response; } ;
struct st_mruby_subreq_t {TYPE_4__ super; TYPE_1__ shortcut; } ;
struct TYPE_25__ {int /*<<< orphan*/  (* start ) (TYPE_8__*) ;int /*<<< orphan*/  proceed; } ;
typedef  TYPE_7__ h2o_mruby_sender_t ;
struct TYPE_18__ {int /*<<< orphan*/  proceed; } ;
struct TYPE_26__ {TYPE_7__* sender; TYPE_12__ super; TYPE_11__* req; TYPE_5__* ctx; } ;
typedef  TYPE_8__ h2o_mruby_generator_t ;
struct TYPE_27__ {int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
typedef  TYPE_9__ h2o_header_t ;
struct TYPE_24__ {int /*<<< orphan*/  headers; int /*<<< orphan*/  mime_attr; int /*<<< orphan*/  content_length; int /*<<< orphan*/  reason; int /*<<< orphan*/  status; } ;
struct TYPE_23__ {int /*<<< orphan*/  shared; } ;
struct TYPE_17__ {TYPE_6__ res; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_TOKEN_DATE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_7__* create_sender (TYPE_8__*,struct st_mruby_subreq_t*,int /*<<< orphan*/ ) ; 
 int h2o_find_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  h2o_mruby_set_response_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_11__*) ; 
 int /*<<< orphan*/  h2o_resp_add_date_header (TYPE_11__*) ; 
 int /*<<< orphan*/  h2o_start_response (TYPE_11__*,TYPE_12__*) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*) ; 

__attribute__((used)) static void send_response_shortcutted(struct st_mruby_subreq_t *subreq)
{
    h2o_mruby_generator_t *generator = subreq->shortcut.response;
    assert(generator != NULL);

    /* copy response except for headers and original */
    generator->req->res.status = subreq->super.res.status;
    generator->req->res.reason = subreq->super.res.reason;
    generator->req->res.content_length = subreq->super.res.content_length;
    generator->req->res.mime_attr = subreq->super.res.mime_attr;

    /* handle response headers */
    int i;
    for (i = 0; i != subreq->super.res.headers.size; ++i) {
        h2o_header_t *header = subreq->super.res.headers.entries + i;
        h2o_mruby_set_response_header(generator->ctx->shared, header->name, header->value, generator->req);
    }
    /* add date: if it's missing from the response */
    if (h2o_find_header(&generator->req->res.headers, H2O_TOKEN_DATE, -1) == -1)
        h2o_resp_add_date_header(generator->req);

    /* setup body sender */
    h2o_mruby_sender_t *sender = create_sender(generator, subreq, mrb_nil_value());
    generator->sender = sender;
    generator->super.proceed = sender->proceed;

    /* start sending response */
    h2o_start_response(generator->req, &generator->super);
    generator->sender->start(generator);
}