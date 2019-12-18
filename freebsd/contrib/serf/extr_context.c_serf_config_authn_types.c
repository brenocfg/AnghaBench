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
struct TYPE_3__ {int authn_types; } ;
typedef  TYPE_1__ serf_context_t ;

/* Variables and functions */

void serf_config_authn_types(serf_context_t *ctx,
                             int authn_types)
{
    ctx->authn_types = authn_types;
}