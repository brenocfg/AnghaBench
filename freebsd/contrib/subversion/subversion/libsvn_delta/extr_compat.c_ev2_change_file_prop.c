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
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct ev2_file_baton {int /*<<< orphan*/  base_revision; int /*<<< orphan*/  path; int /*<<< orphan*/  eb; } ;
struct change_node {int /*<<< orphan*/  unlock; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_ENTRY_LOCK_TOKEN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  apply_propedit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 struct change_node* locate_change (int /*<<< orphan*/ ,char const*) ; 
 char* map_to_repos_relpath (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_node_file ; 

__attribute__((used)) static svn_error_t *
ev2_change_file_prop(void *file_baton,
                     const char *name,
                     const svn_string_t *value,
                     apr_pool_t *scratch_pool)
{
  struct ev2_file_baton *fb = file_baton;

  if (!strcmp(name, SVN_PROP_ENTRY_LOCK_TOKEN) && value == NULL)
    {
      /* We special case the lock token propery deletion, which is the
         server's way of telling the client to unlock the path. */

      /* ### this duplicates much of apply_propedit(). fix in future.  */
      const char *relpath = map_to_repos_relpath(fb->eb, fb->path,
                                                 scratch_pool);
      struct change_node *change = locate_change(fb->eb, relpath);

      change->unlock = TRUE;
    }

  SVN_ERR(apply_propedit(fb->eb, fb->path, svn_node_file, fb->base_revision,
                         name, value, scratch_pool));

  return SVN_NO_ERROR;
}