#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_19__ {TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_ra_session_t ;
struct TYPE_20__ {int /*<<< orphan*/ * prop_hash; int /*<<< orphan*/  path_or_url; } ;
typedef  TYPE_3__ svn_prop_inherited_item_t ;
struct TYPE_21__ {scalar_t__ apr_err; } ;
typedef  TYPE_4__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;
struct TYPE_18__ {TYPE_4__* (* get_dir ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_DIRENT_ALL ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_RA_DAV_FORBIDDEN ; 
 scalar_t__ SVN_ERR_RA_NOT_AUTHORIZED ; 
 TYPE_4__* SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_key_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_this_val (int /*<<< orphan*/ *) ; 
 TYPE_3__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 TYPE_4__* stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_4__*) ; 
 TYPE_4__* svn_error_trace (TYPE_4__*) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_prop_regular_kind ; 
 scalar_t__ svn_property_kind2 (char const*) ; 
 int /*<<< orphan*/  svn_ra_get_repos_root2 (TYPE_2__*,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_session_url (TYPE_2__*,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_reparent (TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sort__array_insert (int /*<<< orphan*/ *,TYPE_3__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_string_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_uri_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_uri_skip_ancestor (char const*,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra__get_inherited_props_walk(svn_ra_session_t *session,
                                 const char *path,
                                 svn_revnum_t revision,
                                 apr_array_header_t **inherited_props,
                                 apr_pool_t *result_pool,
                                 apr_pool_t *scratch_pool)
{
  const char *repos_root_url;
  const char *session_url;
  const char *parent_url;
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);

  *inherited_props =
    apr_array_make(result_pool, 1, sizeof(svn_prop_inherited_item_t *));

  /* Walk to the root of the repository getting inherited
     props for PATH. */
  SVN_ERR(svn_ra_get_repos_root2(session, &repos_root_url, scratch_pool));
  SVN_ERR(svn_ra_get_session_url(session, &session_url, scratch_pool));
  parent_url = session_url;

  while (strcmp(repos_root_url, parent_url))
    {
      apr_hash_index_t *hi;
      apr_hash_t *parent_props;
      apr_hash_t *final_hash = apr_hash_make(result_pool);
      svn_error_t *err;

      svn_pool_clear(iterpool);
      parent_url = svn_uri_dirname(parent_url, scratch_pool);
      SVN_ERR(svn_ra_reparent(session, parent_url, iterpool));
      err = session->vtable->get_dir(session, NULL, NULL,
                                     &parent_props, "",
                                     revision, SVN_DIRENT_ALL,
                                     iterpool);

      /* If the user doesn't have read access to a parent path then
         skip, but allow them to inherit from further up. */
      if (err)
        {
          if ((err->apr_err == SVN_ERR_RA_NOT_AUTHORIZED)
              || (err->apr_err == SVN_ERR_RA_DAV_FORBIDDEN))
            {
              svn_error_clear(err);
              continue;
            }
          else
            {
              return svn_error_trace(err);
            }
        }

      for (hi = apr_hash_first(scratch_pool, parent_props);
           hi;
           hi = apr_hash_next(hi))
        {
          const char *name = apr_hash_this_key(hi);
          apr_ssize_t klen = apr_hash_this_key_len(hi);
          svn_string_t *value = apr_hash_this_val(hi);

          if (svn_property_kind2(name) == svn_prop_regular_kind)
            {
              name = apr_pstrdup(result_pool, name);
              value = svn_string_dup(value, result_pool);
              apr_hash_set(final_hash, name, klen, value);
            }
        }

      if (apr_hash_count(final_hash))
        {
          svn_prop_inherited_item_t *new_iprop =
            apr_palloc(result_pool, sizeof(*new_iprop));
          new_iprop->path_or_url = svn_uri_skip_ancestor(repos_root_url,
                                                         parent_url,
                                                         result_pool);
          new_iprop->prop_hash = final_hash;
          svn_sort__array_insert(*inherited_props, &new_iprop, 0);
        }
    }

  /* Reparent session back to original URL. */
  SVN_ERR(svn_ra_reparent(session, session_url, scratch_pool));

  svn_pool_destroy(iterpool);
  return SVN_NO_ERROR;
}