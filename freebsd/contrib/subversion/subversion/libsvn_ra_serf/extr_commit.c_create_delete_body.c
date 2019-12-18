#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  serf_bucket_t ;
typedef  int /*<<< orphan*/  serf_bucket_alloc_t ;
struct TYPE_4__ {int /*<<< orphan*/  relpath; TYPE_1__* commit_ctx; } ;
typedef  TYPE_2__ delete_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock_tokens; } ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * serf_bucket_aggregate_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__add_xml_header_buckets (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__merge_lock_token_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
create_delete_body(serf_bucket_t **body_bkt,
                   void *baton,
                   serf_bucket_alloc_t *alloc,
                   apr_pool_t *pool /* request pool */,
                   apr_pool_t *scratch_pool)
{
  delete_context_t *ctx = baton;
  serf_bucket_t *body;

  body = serf_bucket_aggregate_create(alloc);

  svn_ra_serf__add_xml_header_buckets(body, alloc);

  svn_ra_serf__merge_lock_token_list(ctx->commit_ctx->lock_tokens,
                                     ctx->relpath, body, alloc, pool);

  *body_bkt = body;
  return SVN_NO_ERROR;
}