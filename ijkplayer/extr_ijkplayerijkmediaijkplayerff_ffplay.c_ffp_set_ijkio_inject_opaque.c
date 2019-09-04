#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {scalar_t__ ijkio_manager_ctx; void* ijkio_inject_opaque; } ;
typedef  TYPE_1__ FFPlayer ;

/* Variables and functions */
 int /*<<< orphan*/  FFP_OPT_CATEGORY_FORMAT ; 
 int /*<<< orphan*/  ffp_set_option_int (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ijkio_app_func_event ; 
 int /*<<< orphan*/  ijkio_manager_create (scalar_t__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ijkio_manager_destroyp (scalar_t__*) ; 
 int /*<<< orphan*/  ijkio_manager_set_callback (scalar_t__,int /*<<< orphan*/ ) ; 

void *ffp_set_ijkio_inject_opaque(FFPlayer *ffp, void *opaque)
{
    if (!ffp)
        return NULL;
    void *prev_weak_thiz = ffp->ijkio_inject_opaque;
    ffp->ijkio_inject_opaque = opaque;

    ijkio_manager_destroyp(&ffp->ijkio_manager_ctx);
    ijkio_manager_create(&ffp->ijkio_manager_ctx, ffp);
    ijkio_manager_set_callback(ffp->ijkio_manager_ctx, ijkio_app_func_event);
    ffp_set_option_int(ffp, FFP_OPT_CATEGORY_FORMAT, "ijkiomanager", (int64_t)(intptr_t)ffp->ijkio_manager_ctx);

    return prev_weak_thiz;
}