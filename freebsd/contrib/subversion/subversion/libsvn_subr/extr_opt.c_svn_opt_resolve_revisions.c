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
struct TYPE_4__ {scalar_t__ kind; } ;
typedef  TYPE_1__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ svn_opt_revision_base ; 
 scalar_t__ svn_opt_revision_head ; 
 scalar_t__ svn_opt_revision_unspecified ; 
 scalar_t__ svn_opt_revision_working ; 

svn_error_t *
svn_opt_resolve_revisions(svn_opt_revision_t *peg_rev,
                          svn_opt_revision_t *op_rev,
                          svn_boolean_t is_url,
                          svn_boolean_t notice_local_mods,
                          apr_pool_t *pool)
{
  if (peg_rev->kind == svn_opt_revision_unspecified)
    {
      if (is_url)
        {
          peg_rev->kind = svn_opt_revision_head;
        }
      else
        {
          if (notice_local_mods)
            peg_rev->kind = svn_opt_revision_working;
          else
            peg_rev->kind = svn_opt_revision_base;
        }
    }

  if (op_rev->kind == svn_opt_revision_unspecified)
    *op_rev = *peg_rev;

  return SVN_NO_ERROR;
}