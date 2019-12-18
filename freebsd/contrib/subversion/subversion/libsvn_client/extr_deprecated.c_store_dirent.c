#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ kind; } ;
typedef  TYPE_1__ svn_lock_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  TYPE_1__ svn_dirent_t ;
struct ls_baton {int /*<<< orphan*/  locks; int /*<<< orphan*/  dirents; int /*<<< orphan*/  pool; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* svn_dirent_dup (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,char const*,TYPE_1__ const*) ; 
 scalar_t__ svn_node_file ; 
 char* svn_path_basename (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
store_dirent(void *baton, const char *path, const svn_dirent_t *dirent,
             const svn_lock_t *lock, const char *abs_path, apr_pool_t *pool)
{
  struct ls_baton *lb = baton;

  /* The dirent is allocated in a temporary pool, so duplicate it into the
     correct pool.  Note, however, that the locks are stored in the correct
     pool already. */
  dirent = svn_dirent_dup(dirent, lb->pool);

  /* An empty path means we are called for the target of the operation.
     For compatibility, we only store the target if it is a file, and we
     store it under the basename of the URL.  Note that this makes it
     impossible to differentiate between the target being a directory with a
     child with the same basename as the target and the target being a file,
     but that's how it was implemented. */
  if (path[0] == '\0')
    {
      if (dirent->kind == svn_node_file)
        {
          const char *base_name = svn_path_basename(abs_path, lb->pool);
          svn_hash_sets(lb->dirents, base_name, dirent);
          if (lock)
            svn_hash_sets(lb->locks, base_name, lock);
        }
    }
  else
    {
      path = apr_pstrdup(lb->pool, path);
      svn_hash_sets(lb->dirents, path, dirent);
      if (lock)
        svn_hash_sets(lb->locks, path, lock);
    }

  return SVN_NO_ERROR;
}