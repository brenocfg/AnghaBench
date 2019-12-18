#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_5__ {TYPE_1__* editor; int /*<<< orphan*/  authz_read_baton; int /*<<< orphan*/  (* authz_read_func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  t_root; scalar_t__ send_copyfrom_args; int /*<<< orphan*/  repos; } ;
typedef  TYPE_2__ report_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* add_file ) (char const*,void*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 char* apr_pstrcat (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (char const*,void*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_closest_copy (int /*<<< orphan*/ **,char const**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_copied_from (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_repos_fs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
add_file_smartly(report_baton_t *b,
                 const char *path,
                 void *parent_baton,
                 const char *o_path,
                 void **new_file_baton,
                 const char **copyfrom_path,
                 svn_revnum_t *copyfrom_rev,
                 apr_pool_t *pool)
{
  /* ### TODO:  use a subpool to do this work, clear it at the end? */
  svn_fs_t *fs = svn_repos_fs(b->repos);
  svn_fs_root_t *closest_copy_root = NULL;
  const char *closest_copy_path = NULL;

  /* Pre-emptively assume no copyfrom args exist. */
  *copyfrom_path = NULL;
  *copyfrom_rev = SVN_INVALID_REVNUM;

  if (b->send_copyfrom_args)
    {
      /* Find the destination of the nearest 'copy event' which may have
         caused o_path@t_root to exist. svn_fs_closest_copy only returns paths
         starting with '/', so make sure o_path always starts with a '/'
         too. */
      if (*o_path != '/')
        o_path = apr_pstrcat(pool, "/", o_path, SVN_VA_NULL);

      SVN_ERR(svn_fs_closest_copy(&closest_copy_root, &closest_copy_path,
                                  b->t_root, o_path, pool));
      if (closest_copy_root != NULL)
        {
          /* If the destination of the copy event is the same path as
             o_path, then we've found something interesting that should
             have 'copyfrom' history. */
          if (strcmp(closest_copy_path, o_path) == 0)
            {
              SVN_ERR(svn_fs_copied_from(copyfrom_rev, copyfrom_path,
                                         closest_copy_root, closest_copy_path,
                                         pool));
              if (b->authz_read_func)
                {
                  svn_boolean_t allowed;
                  svn_fs_root_t *copyfrom_root;
                  SVN_ERR(svn_fs_revision_root(&copyfrom_root, fs,
                                               *copyfrom_rev, pool));
                  SVN_ERR(b->authz_read_func(&allowed, copyfrom_root,
                                             *copyfrom_path, b->authz_read_baton,
                                             pool));
                  if (! allowed)
                    {
                      *copyfrom_path = NULL;
                      *copyfrom_rev = SVN_INVALID_REVNUM;
                    }
                }
            }
        }
    }

  return svn_error_trace(b->editor->add_file(path, parent_baton,
                                             *copyfrom_path, *copyfrom_rev,
                                             pool, new_file_baton));
}