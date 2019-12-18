#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
struct TYPE_4__ {int format; int /*<<< orphan*/  bufferSize; int /*<<< orphan*/  memLevel; int /*<<< orphan*/  windowSize; int /*<<< orphan*/  stream_size; int /*<<< orphan*/  stream_left; int /*<<< orphan*/  state; int /*<<< orphan*/  zstream; scalar_t__ crc; int /*<<< orphan*/  inflate_stream; int /*<<< orphan*/  stream_status; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_1__ deflate_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/  DEFLATE_BUFFER_SIZE ; 
 int /*<<< orphan*/  DEFLATE_MAGIC_SIZE ; 
 int /*<<< orphan*/  DEFLATE_MEMLEVEL ; 
 int /*<<< orphan*/  DEFLATE_WINDOW_SIZE ; 
#define  SERF_DEFLATE_DEFLATE 129 
#define  SERF_DEFLATE_GZIP 128 
 int /*<<< orphan*/  STATE_INIT ; 
 int /*<<< orphan*/  STATE_READING_HEADER ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  serf_bucket_aggregate_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * serf_bucket_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* serf_bucket_mem_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  serf_bucket_type_deflate ; 

serf_bucket_t *serf_bucket_deflate_create(
    serf_bucket_t *stream,
    serf_bucket_alloc_t *allocator,
    int format)
{
    deflate_context_t *ctx;

    ctx = serf_bucket_mem_alloc(allocator, sizeof(*ctx));
    ctx->stream = stream;
    ctx->stream_status = APR_SUCCESS;
    ctx->inflate_stream = serf_bucket_aggregate_create(allocator);
    ctx->format = format;
    ctx->crc = 0;
    /* zstream must be NULL'd out. */
    memset(&ctx->zstream, 0, sizeof(ctx->zstream));

    switch (ctx->format) {
        case SERF_DEFLATE_GZIP:
            ctx->state = STATE_READING_HEADER;
            break;
        case SERF_DEFLATE_DEFLATE:
            /* deflate doesn't have a header. */
            ctx->state = STATE_INIT;
            break;
        default:
            /* Not reachable */
            return NULL;
    }

    /* Initial size of gzip header. */
    ctx->stream_left = ctx->stream_size = DEFLATE_MAGIC_SIZE;

    ctx->windowSize = DEFLATE_WINDOW_SIZE;
    ctx->memLevel = DEFLATE_MEMLEVEL;
    ctx->bufferSize = DEFLATE_BUFFER_SIZE;

    return serf_bucket_create(&serf_bucket_type_deflate, allocator, ctx);
}