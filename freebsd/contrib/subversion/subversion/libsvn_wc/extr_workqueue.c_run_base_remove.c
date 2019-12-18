#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  work_item_baton_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
struct TYPE_6__ {TYPE_3__* next; int /*<<< orphan*/  len; int /*<<< orphan*/  data; TYPE_1__* children; } ;
typedef  TYPE_2__ svn_skel_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;
struct TYPE_7__ {struct TYPE_7__* next; } ;
struct TYPE_5__ {TYPE_2__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int SVN_WC__VERSION ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_skel__parse_int (scalar_t__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_base_get_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_base_remove (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_from_relpath (char const**,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
run_base_remove(work_item_baton_t *wqb,
                svn_wc__db_t *db,
                const svn_skel_t *work_item,
                const char *wri_abspath,
                svn_cancel_func_t cancel_func,
                void *cancel_baton,
                apr_pool_t *scratch_pool)
{
  const svn_skel_t *arg1 = work_item->children->next;
  const char *local_relpath;
  const char *local_abspath;
  svn_revnum_t not_present_rev = SVN_INVALID_REVNUM;
  apr_int64_t val;

  local_relpath = apr_pstrmemdup(scratch_pool, arg1->data, arg1->len);
  SVN_ERR(svn_wc__db_from_relpath(&local_abspath, db, wri_abspath,
                                  local_relpath, scratch_pool, scratch_pool));
  SVN_ERR(svn_skel__parse_int(&val, arg1->next, scratch_pool));

  if (arg1->next->next)
    {
      not_present_rev = (svn_revnum_t)val;

      SVN_ERR(svn_skel__parse_int(&val, arg1->next->next, scratch_pool));
    }
  else
    {
      svn_boolean_t keep_not_present;

      SVN_ERR_ASSERT(SVN_WC__VERSION <= 28); /* Case unused in later versions*/

      keep_not_present = (val != 0);

      if (keep_not_present)
        {
          SVN_ERR(svn_wc__db_base_get_info(NULL, NULL,
                                           &not_present_rev, NULL,
                                           NULL, NULL, NULL,
                                           NULL, NULL, NULL, NULL, NULL, NULL,
                                           NULL, NULL, NULL,
                                           db, local_abspath,
                                           scratch_pool, scratch_pool));
        }
    }

  SVN_ERR(svn_wc__db_base_remove(db, local_abspath,
                                 FALSE /* keep_as_working */,
                                 SVN_IS_VALID_REVNUM(not_present_rev), FALSE,
                                 not_present_rev,
                                 NULL, NULL, scratch_pool));

  return SVN_NO_ERROR;
}