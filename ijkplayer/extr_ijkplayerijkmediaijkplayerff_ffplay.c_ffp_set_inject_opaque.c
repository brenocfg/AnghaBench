#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_8__ {int /*<<< orphan*/  func_on_app_event; } ;
struct TYPE_7__ {TYPE_4__* app_ctx; void* inject_opaque; } ;
typedef  TYPE_1__ FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  FFP_OPT_CATEGORY_FORMAT ; 
 int /*<<< orphan*/  app_func_event ; 
 int /*<<< orphan*/  av_application_closep (TYPE_4__**) ; 
 int /*<<< orphan*/  av_application_open (TYPE_4__**,TYPE_1__*) ; 
 int /*<<< orphan*/  ffp_set_option_int (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void *ffp_set_inject_opaque(FFPlayer *ffp, void *opaque)
{
    if (!ffp)
        return NULL;
    void *prev_weak_thiz = ffp->inject_opaque;
    ffp->inject_opaque = opaque;

    av_application_closep(&ffp->app_ctx);
    av_application_open(&ffp->app_ctx, ffp);
    ffp_set_option_int(ffp, FFP_OPT_CATEGORY_FORMAT, "ijkapplication", (int64_t)(intptr_t)ffp->app_ctx);

    ffp->app_ctx->func_on_app_event = app_func_event;
    return prev_weak_thiz;
}