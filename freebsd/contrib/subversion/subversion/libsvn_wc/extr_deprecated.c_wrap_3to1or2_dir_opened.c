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
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 

__attribute__((used)) static svn_error_t *
wrap_3to1or2_dir_opened(svn_wc_adm_access_t *adm_access,
                        svn_boolean_t *tree_conflicted,
                        const char *path,
                        svn_revnum_t rev,
                        void *diff_baton)
{
  if (tree_conflicted)
    *tree_conflicted = FALSE;
  /* Do nothing. */
  return SVN_NO_ERROR;
}