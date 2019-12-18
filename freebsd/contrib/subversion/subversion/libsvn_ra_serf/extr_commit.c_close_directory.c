#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {int /*<<< orphan*/  path; int /*<<< orphan*/  base_revision; int /*<<< orphan*/  prop_changes; int /*<<< orphan*/  relpath; int /*<<< orphan*/ * commit_ctx; int /*<<< orphan*/ * pool; } ;
typedef  TYPE_1__ proppatch_context_t ;
struct TYPE_7__ {TYPE_5__* commit_ctx; int /*<<< orphan*/  pool; int /*<<< orphan*/  working_url; int /*<<< orphan*/  url; int /*<<< orphan*/  base_revision; int /*<<< orphan*/  prop_changes; int /*<<< orphan*/  relpath; } ;
typedef  TYPE_2__ dir_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_8__ {int /*<<< orphan*/  open_batons; int /*<<< orphan*/  session; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ USING_HTTPV2_COMMIT_SUPPORT (TYPE_5__*) ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ ) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  proppatch_resource (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
close_directory(void *dir_baton,
                apr_pool_t *pool)
{
  dir_context_t *dir = dir_baton;

  /* Huh?  We're going to be called before the texts are sent.  Ugh.
   * Therefore, just wave politely at our caller.
   */

  /* PROPPATCH our prop change and pass it along.  */
  if (apr_hash_count(dir->prop_changes))
    {
      proppatch_context_t *proppatch_ctx;

      proppatch_ctx = apr_pcalloc(pool, sizeof(*proppatch_ctx));
      proppatch_ctx->pool = pool;
      proppatch_ctx->commit_ctx = NULL /* No lock tokens necessary */;
      proppatch_ctx->relpath = dir->relpath;
      proppatch_ctx->prop_changes = dir->prop_changes;
      proppatch_ctx->base_revision = dir->base_revision;

      if (USING_HTTPV2_COMMIT_SUPPORT(dir->commit_ctx))
        {
          proppatch_ctx->path = dir->url;
        }
      else
        {
          proppatch_ctx->path = dir->working_url;
        }

      SVN_ERR(proppatch_resource(dir->commit_ctx->session,
                                 proppatch_ctx, dir->pool));
    }

  dir->commit_ctx->open_batons--;

  return SVN_NO_ERROR;
}