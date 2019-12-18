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
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  svn_wc__db_is_switched (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
child_is_disjoint(svn_boolean_t *disjoint,
                  svn_wc__db_t *db,
                  const char *local_abspath,
                  apr_pool_t *scratch_pool)
{
  svn_boolean_t is_switched;

  /* Check if the parent directory knows about this node */
  SVN_ERR(svn_wc__db_is_switched(disjoint, &is_switched, NULL,
                                 db, local_abspath, scratch_pool));

  if (*disjoint)
    return SVN_NO_ERROR;

  if (is_switched)
    *disjoint = TRUE;

  return SVN_NO_ERROR;
}