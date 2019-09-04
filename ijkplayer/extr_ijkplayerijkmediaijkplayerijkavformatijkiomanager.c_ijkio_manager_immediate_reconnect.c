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
struct TYPE_5__ {TYPE_1__* ijkio_app_ctx; } ;
struct TYPE_4__ {int active_reconnect; } ;
typedef  TYPE_2__ IjkIOManagerContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void ijkio_manager_immediate_reconnect(IjkIOManagerContext *h) {
    av_log(NULL, AV_LOG_INFO, "ijkio manager immediate reconnect\n");
    if (!h || !h->ijkio_app_ctx) {
        return;
    }
    h->ijkio_app_ctx->active_reconnect = 1;
}