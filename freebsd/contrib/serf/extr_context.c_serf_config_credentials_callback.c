#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  serf_credentials_callback_t ;
struct TYPE_3__ {int /*<<< orphan*/  cred_cb; } ;
typedef  TYPE_1__ serf_context_t ;

/* Variables and functions */

void serf_config_credentials_callback(serf_context_t *ctx,
                                      serf_credentials_callback_t cred_cb)
{
    ctx->cred_cb = cred_cb;
}