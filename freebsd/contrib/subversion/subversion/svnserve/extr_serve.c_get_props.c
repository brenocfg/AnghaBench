#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  server; } ;
typedef  TYPE_1__ authz_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_ENTRY_COMMITTED_DATE ; 
 int /*<<< orphan*/  SVN_PROP_ENTRY_COMMITTED_REV ; 
 int /*<<< orphan*/  SVN_PROP_ENTRY_LAST_AUTHOR ; 
 int /*<<< orphan*/  SVN_PROP_ENTRY_UUID ; 
 int /*<<< orphan*/  authz_check_access_cb_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_get_uuid (int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_node_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_root_fs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_fs_get_inherited_props (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_get_committed_info (int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_string_create (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_string_createf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
get_props(apr_hash_t **props,
          apr_array_header_t **iprops,
          authz_baton_t *b,
          svn_fs_root_t *root,
          const char *path,
          apr_pool_t *pool)
{
  /* Get the explicit properties. */
  if (props)
    {
      svn_string_t *str;
      svn_revnum_t crev;
      const char *cdate, *cauthor, *uuid;

      SVN_ERR(svn_fs_node_proplist(props, root, path, pool));

      /* Hardcode the values for the committed revision, date, and author. */
      SVN_ERR(svn_repos_get_committed_info(&crev, &cdate, &cauthor, root,
                                           path, pool));
      str = svn_string_createf(pool, "%ld", crev);
      svn_hash_sets(*props, SVN_PROP_ENTRY_COMMITTED_REV, str);
      str = (cdate) ? svn_string_create(cdate, pool) : NULL;
      svn_hash_sets(*props, SVN_PROP_ENTRY_COMMITTED_DATE, str);
      str = (cauthor) ? svn_string_create(cauthor, pool) : NULL;
      svn_hash_sets(*props, SVN_PROP_ENTRY_LAST_AUTHOR, str);

      /* Hardcode the values for the UUID. */
      SVN_ERR(svn_fs_get_uuid(svn_fs_root_fs(root), &uuid, pool));
      str = (uuid) ? svn_string_create(uuid, pool) : NULL;
      svn_hash_sets(*props, SVN_PROP_ENTRY_UUID, str);
    }

  /* Get any inherited properties the user is authorized to. */
  if (iprops)
    {
      SVN_ERR(svn_repos_fs_get_inherited_props(
                iprops, root, path, NULL,
                authz_check_access_cb_func(b->server),
                b, pool, pool));
    }

  return SVN_NO_ERROR;
}