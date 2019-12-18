#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* repository; } ;
typedef  TYPE_3__ server_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_5__ {TYPE_1__* fs_path; int /*<<< orphan*/  repos_url; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 char* svn_fspath__canonicalize (char const*,int /*<<< orphan*/ *) ; 
 char* svn_fspath__join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_path_is_url (char const*) ; 
 char* svn_uri_skip_ancestor (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
get_normalized_repo_rel_path(void *baton,
                             const char *path,
                             apr_pool_t *pool)
{
  server_baton_t *sb = baton;

  if (svn_path_is_url(path))
    {
      /* This is a copyfrom URL. */
      path = svn_uri_skip_ancestor(sb->repository->repos_url, path, pool);
      path = svn_fspath__canonicalize(path, pool);
    }
  else
    {
      /* This is a base-relative path. */
      if ((path)[0] != '/')
        /* Get an absolute path for use in the FS. */
        path = svn_fspath__join(sb->repository->fs_path->data, path, pool);
    }

  return path;
}