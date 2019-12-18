#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int iteration_count; int file_count; scalar_t__ last_notified_revision; void* hint; int /*<<< orphan*/  pool; int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  (* notify_func ) (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ verify_walker_baton_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {scalar_t__ revision; } ;
typedef  TYPE_2__ representation_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__check_rep (TYPE_2__*,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
verify_walker(representation_t *rep,
              void *baton,
              svn_fs_t *fs,
              apr_pool_t *scratch_pool)
{
  verify_walker_baton_t *walker_baton = baton;
  void *previous_hint;

  /* notify and free resources periodically */
  if (   walker_baton->iteration_count > 1000
      || walker_baton->file_count > 16)
    {
      if (   walker_baton->notify_func
          && rep->revision != walker_baton->last_notified_revision)
        {
          walker_baton->notify_func(rep->revision,
                                    walker_baton->notify_baton,
                                    scratch_pool);
          walker_baton->last_notified_revision = rep->revision;
        }

      svn_pool_clear(walker_baton->pool);

      walker_baton->iteration_count = 0;
      walker_baton->file_count = 0;
      walker_baton->hint = NULL;
    }

  /* access the repo data */
  previous_hint = walker_baton->hint;
  SVN_ERR(svn_fs_fs__check_rep(rep, fs, &walker_baton->hint,
                               walker_baton->pool));

  /* update resource usage counters */
  walker_baton->iteration_count++;
  if (previous_hint != walker_baton->hint)
    walker_baton->file_count++;

  return SVN_NO_ERROR;
}