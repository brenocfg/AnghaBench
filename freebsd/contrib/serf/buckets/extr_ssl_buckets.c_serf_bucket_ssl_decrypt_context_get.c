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
struct TYPE_4__ {int /*<<< orphan*/ * ssl_ctx; } ;
typedef  TYPE_1__ ssl_context_t ;
typedef  int /*<<< orphan*/  serf_ssl_context_t ;
struct TYPE_5__ {TYPE_1__* data; } ;
typedef  TYPE_2__ serf_bucket_t ;

/* Variables and functions */

serf_ssl_context_t *serf_bucket_ssl_decrypt_context_get(
     serf_bucket_t *bucket)
{
    ssl_context_t *ctx = bucket->data;
    return ctx->ssl_ctx;
}