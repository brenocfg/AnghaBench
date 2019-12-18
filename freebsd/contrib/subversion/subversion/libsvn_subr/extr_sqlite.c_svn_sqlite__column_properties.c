#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_skel__parse (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__parse_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* svn_sqlite__column_blob (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_sqlite__column_properties(apr_hash_t **props,
                              svn_sqlite__stmt_t *stmt,
                              int column,
                              apr_pool_t *result_pool,
                              apr_pool_t *scratch_pool)
{
  apr_size_t len;
  const void *val;

  /* svn_skel__parse_proplist copies everything needed to result_pool */
  val = svn_sqlite__column_blob(stmt, column, &len, NULL);
  if (val == NULL)
    {
      *props = NULL;
      return SVN_NO_ERROR;
    }

  SVN_ERR(svn_skel__parse_proplist(props,
                                   svn_skel__parse(val, len, scratch_pool),
                                   result_pool));

  return SVN_NO_ERROR;
}