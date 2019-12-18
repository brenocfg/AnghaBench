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
typedef  int /*<<< orphan*/  (* svn_repos_authz_func_t ) (scalar_t__*,int /*<<< orphan*/ *,char const*,void*,int /*<<< orphan*/ *) ;
struct TYPE_4__ {int /*<<< orphan*/ * prop_hash; int /*<<< orphan*/  path_or_url; } ;
typedef  TYPE_1__ svn_prop_inherited_item_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_fs_node_prop (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_node_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 char* svn_fspath__dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sort__array_insert (int /*<<< orphan*/ *,TYPE_1__**,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_repos_fs_get_inherited_props(apr_array_header_t **inherited_props_p,
                                 svn_fs_root_t *root,
                                 const char *path,
                                 const char *propname,
                                 svn_repos_authz_func_t authz_read_func,
                                 void *authz_read_baton,
                                 apr_pool_t *result_pool,
                                 apr_pool_t *scratch_pool)
{
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);
  apr_array_header_t *inherited_props;
  const char *parent_path = path;

  inherited_props = apr_array_make(result_pool, 1,
                                   sizeof(svn_prop_inherited_item_t *));
  while (!(parent_path[0] == '/' && parent_path[1] == '\0'))
    {
      svn_boolean_t allowed = TRUE;
      apr_hash_t *parent_properties = NULL;

      svn_pool_clear(iterpool);
      parent_path = svn_fspath__dirname(parent_path, scratch_pool);

      if (authz_read_func)
        SVN_ERR(authz_read_func(&allowed, root, parent_path,
                                authz_read_baton, iterpool));
      if (allowed)
        {
          if (propname)
            {
              svn_string_t *propval;

              SVN_ERR(svn_fs_node_prop(&propval, root, parent_path, propname,
                                       result_pool));
              if (propval)
                {
                  parent_properties = apr_hash_make(result_pool);
                  svn_hash_sets(parent_properties, propname, propval);
                }
            }
          else
            {
              SVN_ERR(svn_fs_node_proplist(&parent_properties, root,
                                           parent_path, result_pool));
            }

          if (parent_properties && apr_hash_count(parent_properties))
            {
              svn_prop_inherited_item_t *i_props =
                apr_pcalloc(result_pool, sizeof(*i_props));
              i_props->path_or_url =
                apr_pstrdup(result_pool, parent_path + 1);
              i_props->prop_hash = parent_properties;
              /* Build the output array in depth-first order. */
              svn_sort__array_insert(inherited_props, &i_props, 0);
            }
        }
    }

  svn_pool_destroy(iterpool);

  *inherited_props_p = inherited_props;
  return SVN_NO_ERROR;
}