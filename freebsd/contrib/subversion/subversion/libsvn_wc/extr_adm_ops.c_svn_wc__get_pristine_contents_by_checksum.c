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
struct TYPE_6__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_7__ {char const* wri_abspath; int /*<<< orphan*/  const* checksum; TYPE_1__* wc_ctx; } ;
typedef  TYPE_2__ get_pristine_lazyopen_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_pristine_lazyopen_func ; 
 int /*<<< orphan*/ * svn_stream_lazyopen_create (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_pristine_check (scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__get_pristine_contents_by_checksum(svn_stream_t **contents,
                                          svn_wc_context_t *wc_ctx,
                                          const char *wri_abspath,
                                          const svn_checksum_t *checksum,
                                          apr_pool_t *result_pool,
                                          apr_pool_t *scratch_pool)
{
  svn_boolean_t present;

  *contents = NULL;

  SVN_ERR(svn_wc__db_pristine_check(&present, wc_ctx->db, wri_abspath,
                                    checksum, scratch_pool));

  if (present)
    {
      get_pristine_lazyopen_baton_t *gpl_baton;

      gpl_baton = apr_pcalloc(result_pool, sizeof(*gpl_baton));
      gpl_baton->wc_ctx = wc_ctx;
      gpl_baton->wri_abspath = wri_abspath;
      gpl_baton->checksum = checksum;

      *contents = svn_stream_lazyopen_create(get_pristine_lazyopen_func,
                                             gpl_baton, FALSE, result_pool);
    }

  return SVN_NO_ERROR;
}