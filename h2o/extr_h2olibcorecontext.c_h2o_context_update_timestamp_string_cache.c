#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  h2o_timestamp_string_t ;
struct TYPE_7__ {int /*<<< orphan*/  tv_sec; } ;
struct TYPE_8__ {TYPE_1__ tv_at; TYPE_4__* value; } ;
struct TYPE_9__ {TYPE_2__ _timestamp_cache; } ;
typedef  TYPE_3__ h2o_context_t ;
struct TYPE_10__ {int /*<<< orphan*/  log; int /*<<< orphan*/  rfc1123; } ;

/* Variables and functions */
 int /*<<< orphan*/  gmtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 TYPE_4__* h2o_mem_alloc_shared (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mem_release_shared (TYPE_4__*) ; 
 int /*<<< orphan*/  h2o_time2str_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_time2str_rfc1123 (int /*<<< orphan*/ ,struct tm*) ; 

void h2o_context_update_timestamp_string_cache(h2o_context_t *ctx)
{
    struct tm gmt;
    if (ctx->_timestamp_cache.value != NULL)
        h2o_mem_release_shared(ctx->_timestamp_cache.value);
    ctx->_timestamp_cache.value = h2o_mem_alloc_shared(NULL, sizeof(h2o_timestamp_string_t), NULL);
    gmtime_r(&ctx->_timestamp_cache.tv_at.tv_sec, &gmt);
    h2o_time2str_rfc1123(ctx->_timestamp_cache.value->rfc1123, &gmt);
    h2o_time2str_log(ctx->_timestamp_cache.value->log, ctx->_timestamp_cache.tv_at.tv_sec);
}