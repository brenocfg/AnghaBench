#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* data; int /*<<< orphan*/ * type; int /*<<< orphan*/  allocator; } ;
typedef  TYPE_1__ serf_bucket_t ;
struct TYPE_7__ {char const* method; char const* uri; TYPE_1__* body; int /*<<< orphan*/  headers; } ;
typedef  TYPE_2__ request_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  serf_bucket_headers_create (int /*<<< orphan*/ ) ; 
 TYPE_2__* serf_bucket_mem_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  serf_bucket_type_request ; 

void serf_bucket_request_become(
    serf_bucket_t *bucket,
    const char *method,
    const char *uri,
    serf_bucket_t *body)
{
    request_context_t *ctx;

    ctx = serf_bucket_mem_alloc(bucket->allocator, sizeof(*ctx));
    ctx->method = method;
    ctx->uri = uri;
    ctx->headers = serf_bucket_headers_create(bucket->allocator);
    ctx->body = body;

    bucket->type = &serf_bucket_type_request;
    bucket->data = ctx;

    /* The allocator remains the same. */
}