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
typedef  int /*<<< orphan*/  svn_wc_context_t ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/ * svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_MERGEINFO ; 
 int /*<<< orphan*/  svn_mergeinfo_parse (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_prop_get2 (TYPE_1__ const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client__parse_mergeinfo(svn_mergeinfo_t *mergeinfo,
                            svn_wc_context_t *wc_ctx,
                            const char *local_abspath,
                            apr_pool_t *result_pool,
                            apr_pool_t *scratch_pool)
{
  const svn_string_t *propval;

  *mergeinfo = NULL;

  /* ### Use svn_wc_prop_get() would actually be sufficient for now.
     ### DannyB thinks that later we'll need behavior more like
     ### svn_client__get_prop_from_wc(). */
  SVN_ERR(svn_wc_prop_get2(&propval, wc_ctx, local_abspath, SVN_PROP_MERGEINFO,
                           scratch_pool, scratch_pool));
  if (propval)
    SVN_ERR(svn_mergeinfo_parse(mergeinfo, propval->data, result_pool));

  return SVN_NO_ERROR;
}