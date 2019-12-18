#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_8__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_history_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_9__ {scalar_t__ revision; scalar_t__ is_interesting; int /*<<< orphan*/  path; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_2__ fs_history_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* assemble_history (int /*<<< orphan*/ *,char*,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  history_prev (TYPE_1__**,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
fs_history_prev(svn_fs_history_t **prev_history_p,
                svn_fs_history_t *history,
                svn_boolean_t cross_copies,
                apr_pool_t *result_pool,
                apr_pool_t *scratch_pool)
{
  svn_fs_history_t *prev_history = NULL;
  fs_history_data_t *fhd = history->fsap_data;
  svn_fs_t *fs = fhd->fs;

  /* Special case: the root directory changes in every single
     revision, no exceptions.  And, the root can't be the target (or
     child of a target -- duh) of a copy.  So, if that's our path,
     then we need only decrement our revision by 1, and there you go. */
  if (strcmp(fhd->path, "/") == 0)
    {
      if (! fhd->is_interesting)
        prev_history = assemble_history(fs, "/", fhd->revision,
                                        1, NULL, SVN_INVALID_REVNUM,
                                        SVN_INVALID_REVNUM, NULL,
                                        result_pool);
      else if (fhd->revision > 0)
        prev_history = assemble_history(fs, "/", fhd->revision - 1,
                                        1, NULL, SVN_INVALID_REVNUM,
                                        SVN_INVALID_REVNUM, NULL,
                                        result_pool);
    }
  else
    {
      apr_pool_t *iterpool = svn_pool_create(scratch_pool);
      prev_history = history;

      while (1)
        {
          svn_pool_clear(iterpool);
          SVN_ERR(history_prev(&prev_history, prev_history, cross_copies,
                               result_pool, iterpool));

          if (! prev_history)
            break;
          fhd = prev_history->fsap_data;
          if (fhd->is_interesting)
            break;
        }

      svn_pool_destroy(iterpool);
    }

  *prev_history_p = prev_history;
  return SVN_NO_ERROR;
}