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
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_6__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_history_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct history_prev_args {int /*<<< orphan*/ * pool; int /*<<< orphan*/  cross_copies; TYPE_1__* history; TYPE_1__** prev_history_p; } ;
struct TYPE_7__ {scalar_t__ revision; scalar_t__ is_interesting; int /*<<< orphan*/  path; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_2__ base_history_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_1__* assemble_history (int /*<<< orphan*/ *,char*,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svn_fs_base__retry_txn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct history_prev_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_history_prev ; 

__attribute__((used)) static svn_error_t *
base_history_prev(svn_fs_history_t **prev_history_p,
                  svn_fs_history_t *history,
                  svn_boolean_t cross_copies,
                  apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  svn_fs_history_t *prev_history = NULL;
  base_history_data_t *bhd = history->fsap_data;
  svn_fs_t *fs = bhd->fs;

  /* Special case: the root directory changes in every single
     revision, no exceptions.  And, the root can't be the target (or
     child of a target -- duh) of a copy.  So, if that's our path,
     then we need only decrement our revision by 1, and there you go. */
  if (strcmp(bhd->path, "/") == 0)
    {
      if (! bhd->is_interesting)
        prev_history = assemble_history(fs, "/", bhd->revision,
                                        1, NULL, SVN_INVALID_REVNUM,
                                        result_pool);
      else if (bhd->revision > 0)
        prev_history = assemble_history(fs, "/", bhd->revision - 1,
                                        1, NULL, SVN_INVALID_REVNUM,
                                        result_pool);
    }
  else
    {
      struct history_prev_args args;
      prev_history = history;

      while (1)
        {
          /* Get a trail, and get to work. */

          args.prev_history_p = &prev_history;
          args.history = prev_history;
          args.cross_copies = cross_copies;
          args.pool = result_pool;
          SVN_ERR(svn_fs_base__retry_txn(fs, txn_body_history_prev, &args,
                                         FALSE, result_pool));
          if (! prev_history)
            break;
          bhd = prev_history->fsap_data;
          if (bhd->is_interesting)
            break;
        }
    }

  *prev_history_p = prev_history;
  return SVN_NO_ERROR;
}