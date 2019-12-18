#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_ra_serf__stream_bucket_errfunc_t ;
struct TYPE_6__ {TYPE_1__* read_baton; int /*<<< orphan*/  read; } ;
struct TYPE_5__ {TYPE_2__ databuf; void* errfunc_baton; int /*<<< orphan*/  errfunc; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_1__ stream_bucket_ctx_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;

/* Variables and functions */
 int /*<<< orphan*/ * serf_bucket_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* serf_bucket_mem_calloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  serf_databuf_init (TYPE_2__*) ; 
 int /*<<< orphan*/  stream_bucket_vtable ; 
 int /*<<< orphan*/  stream_reader ; 

serf_bucket_t *
svn_ra_serf__create_stream_bucket(svn_stream_t *stream,
                                  serf_bucket_alloc_t *allocator,
                                  svn_ra_serf__stream_bucket_errfunc_t errfunc,
                                  void *errfunc_baton)
{
  stream_bucket_ctx_t *ctx;

  ctx = serf_bucket_mem_calloc(allocator, sizeof(*ctx));
  ctx->stream = stream;
  ctx->errfunc = errfunc;
  ctx->errfunc_baton = errfunc_baton;
  serf_databuf_init(&ctx->databuf);
  ctx->databuf.read = stream_reader;
  ctx->databuf.read_baton = ctx;

  return serf_bucket_create(&stream_bucket_vtable, allocator, ctx);
}