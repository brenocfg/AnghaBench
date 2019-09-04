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
struct TYPE_4__ {void* func_ijkio_on_app_event; } ;
typedef  TYPE_2__ IjkIOManagerContext ;

/* Variables and functions */

int ijkio_manager_set_callback(IjkIOManagerContext *h, void *callback) {
    if (!h)
        return -1;

    h->ijkio_app_ctx->func_ijkio_on_app_event = callback;

    return 0;
}