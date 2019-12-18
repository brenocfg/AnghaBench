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
typedef  int /*<<< orphan*/  svn_error_t ;
struct edit_baton {char* switch_repos_relpath; char* target_basename; } ;
struct dir_baton {int /*<<< orphan*/  new_repos_relpath; int /*<<< orphan*/ * parent_baton; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 char* svn_dirent_basename (char const*,int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
calculate_repos_relpath(const char **new_repos_relpath,
                        const char *local_abspath,
                        const char *old_repos_relpath,
                        struct edit_baton *eb,
                        struct dir_baton *pb,
                        apr_pool_t *result_pool,
                        apr_pool_t *scratch_pool)
{
  const char *name = svn_dirent_basename(local_abspath, NULL);

  /* Figure out the new_repos_relpath for this directory. */
  if (eb->switch_repos_relpath)
    {
      /* Handle switches... */

      if (pb == NULL)
        {
          if (*eb->target_basename == '\0')
            {
              /* No parent baton and target_basename=="" means that we are
                 the target of the switch. Thus, our new_repos_relpath will be
                 the switch_repos_relpath.  */
              *new_repos_relpath = eb->switch_repos_relpath;
            }
          else
            {
              /* This node is NOT the target of the switch (one of our
                 children is the target); therefore, it must already exist.
                 Get its old REPOS_RELPATH, as it won't be changing.  */
              *new_repos_relpath = apr_pstrdup(result_pool, old_repos_relpath);
            }
        }
      else
        {
          /* This directory is *not* the root (has a parent). If there is
             no grandparent, then we may have anchored at the parent,
             and self is the target. If we match the target, then set
             new_repos_relpath to the switch_repos_relpath.

             Otherwise, we simply extend new_repos_relpath from the parent.  */

          if (pb->parent_baton == NULL
              && strcmp(eb->target_basename, name) == 0)
            *new_repos_relpath = eb->switch_repos_relpath;
          else
            *new_repos_relpath = svn_relpath_join(pb->new_repos_relpath, name,
                                                  result_pool);
        }
    }
  else  /* must be an update */
    {
      /* If we are adding the node, then simply extend the parent's
         relpath for our own.  */
      if (old_repos_relpath == NULL)
        {
          SVN_ERR_ASSERT(pb != NULL);
          *new_repos_relpath = svn_relpath_join(pb->new_repos_relpath, name,
                                                result_pool);
        }
      else
        {
          *new_repos_relpath = apr_pstrdup(result_pool, old_repos_relpath);
        }
    }

  return SVN_NO_ERROR;
}