#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_path_change2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_9__ {int /*<<< orphan*/  changed_paths; int /*<<< orphan*/  deletions; } ;
typedef  TYPE_3__ process_changes_baton_t ;
struct TYPE_8__ {int len; char* data; } ;
struct TYPE_7__ {scalar_t__ change_kind; } ;
struct TYPE_10__ {TYPE_2__ path; TYPE_1__ info; } ;
typedef  TYPE_4__ change_t ;
typedef  int apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ ,void const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,void const**,int*,void**) ; 
 int /*<<< orphan*/  fold_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ svn_fs_path_change_delete ; 
 scalar_t__ svn_fs_path_change_replace ; 
 char* svn_fspath__skip_ancestor (char*,void const*) ; 

__attribute__((used)) static svn_error_t *
process_changes(void *baton_p,
                change_t *change,
                apr_pool_t *scratch_pool)
{
  process_changes_baton_t *baton = baton_p;

  SVN_ERR(fold_change(baton->changed_paths, baton->deletions, change));

  /* Now, if our change was a deletion or replacement, we have to
     blow away any changes thus far on paths that are (or, were)
     children of this path.
     ### i won't bother with another iteration pool here -- at
     most we talking about a few extra dups of paths into what
     is already a temporary subpool.
  */

  if ((change->info.change_kind == svn_fs_path_change_delete)
       || (change->info.change_kind == svn_fs_path_change_replace))
    {
      apr_hash_index_t *hi;

      /* a potential child path must contain at least 2 more chars
         (the path separator plus at least one char for the name).
         Also, we should not assume that all paths have been normalized
         i.e. some might have trailing path separators.
      */
      apr_ssize_t path_len = change->path.len;
      apr_ssize_t min_child_len = path_len == 0
                                ? 1
                                : change->path.data[path_len-1] == '/'
                                    ? path_len + 1
                                    : path_len + 2;

      /* CAUTION: This is the inner loop of an O(n^2) algorithm.
         The number of changes to process may be >> 1000.
         Therefore, keep the inner loop as tight as possible.
      */
      for (hi = apr_hash_first(scratch_pool, baton->changed_paths);
           hi;
           hi = apr_hash_next(hi))
        {
          /* KEY is the path. */
          const void *path;
          apr_ssize_t klen;
          svn_fs_path_change2_t *old_change;
          apr_hash_this(hi, &path, &klen, (void**)&old_change);

          /* If we come across a child of our path, remove it.
             Call svn_fspath__skip_ancestor only if there is a chance that
             this is actually a sub-path.
           */
          if (klen >= min_child_len)
            {
              const char *child;

              child = svn_fspath__skip_ancestor(change->path.data, path);
              if (child && child[0] != '\0')
                {
                  apr_hash_set(baton->changed_paths, path, klen, NULL);
                }
            }
        }
    }

  return SVN_NO_ERROR;
}