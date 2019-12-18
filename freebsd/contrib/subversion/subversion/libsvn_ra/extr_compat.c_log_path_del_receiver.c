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
struct TYPE_5__ {int /*<<< orphan*/  revision; int /*<<< orphan*/  changed_paths2; } ;
typedef  TYPE_1__ svn_log_entry_t ;
struct TYPE_6__ {char action; } ;
typedef  TYPE_2__ svn_log_changed_path_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {int /*<<< orphan*/  revision_deleted; int /*<<< orphan*/  path; } ;
typedef  TYPE_3__ log_path_del_rev_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ svn_path_compare_paths (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static svn_error_t *
log_path_del_receiver(void *baton,
                      svn_log_entry_t *log_entry,
                      apr_pool_t *pool)
{
  log_path_del_rev_t *b = baton;
  apr_hash_index_t *hi;

  /* No paths were changed in this revision.  Nothing to do. */
  if (! log_entry->changed_paths2)
    return SVN_NO_ERROR;

  for (hi = apr_hash_first(pool, log_entry->changed_paths2);
       hi != NULL;
       hi = apr_hash_next(hi))
    {
      void *val;
      char *path;
      svn_log_changed_path_t *log_item;

      apr_hash_this(hi, (void *) &path, NULL, &val);
      log_item = val;
      if (svn_path_compare_paths(b->path, path) == 0
          && (log_item->action == 'D' || log_item->action == 'R'))
        {
          /* Found the first deletion or replacement, we are done. */
          b->revision_deleted = log_entry->revision;
          break;
        }
    }
  return SVN_NO_ERROR;
}