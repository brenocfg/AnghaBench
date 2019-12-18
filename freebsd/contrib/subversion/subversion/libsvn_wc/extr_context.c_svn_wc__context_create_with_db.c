#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  close_db_on_destroy; int /*<<< orphan*/ * db; int /*<<< orphan*/ * state_pool; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_config_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_ctx_apr ; 

svn_error_t *
svn_wc__context_create_with_db(svn_wc_context_t **wc_ctx,
                               svn_config_t *config,
                               svn_wc__db_t *db,
                               apr_pool_t *result_pool)
{
  svn_wc_context_t *ctx = apr_pcalloc(result_pool, sizeof(*ctx));

  /* Create the state pool.  We don't put the wc_db in it, because it's
     already open in a separate pool somewhere.  We also won't close the
     wc_db when we destroy the context, since it's not ours to close. */
  ctx->state_pool = result_pool;
  ctx->db = db;
  ctx->close_db_on_destroy = FALSE;

  apr_pool_cleanup_register(result_pool, ctx, close_ctx_apr,
                            apr_pool_cleanup_null);

  *wc_ctx = ctx;

  return SVN_NO_ERROR;
}