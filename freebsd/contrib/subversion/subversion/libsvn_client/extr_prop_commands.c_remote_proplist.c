#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_proplist_receiver2_t ;
typedef  scalar_t__ svn_prop_kind_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {scalar_t__ kind; } ;
typedef  TYPE_1__ svn_dirent_t ;
typedef  scalar_t__ svn_depth_t ;
typedef  int /*<<< orphan*/ * (* svn_cancel_func_t ) (void*) ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_ssize_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_DIRENT_KIND ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_NODE_UNKNOWN_KIND ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_set (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_key_len (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * call_receiver (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_client__iprop_relpaths_to_urls (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_depth_empty ; 
 scalar_t__ svn_depth_files ; 
 scalar_t__ svn_depth_immediates ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 char* svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ svn_prop_regular_kind ; 
 scalar_t__ svn_property_kind2 (char const*) ; 
 int /*<<< orphan*/ * svn_ra_get_dir2 (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_get_file (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_get_inherited_props (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_ra_get_repos_root2 (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
remote_proplist(const char *target_prefix,
                const char *target_relative,
                svn_node_kind_t kind,
                svn_revnum_t revnum,
                svn_ra_session_t *ra_session,
                svn_boolean_t get_explicit_props,
                svn_boolean_t get_target_inherited_props,
                svn_depth_t depth,
                svn_proplist_receiver2_t receiver,
                void *receiver_baton,
                svn_cancel_func_t cancel_func,
                void *cancel_baton,
                apr_pool_t *scratch_pool)
{
  apr_hash_t *dirents;
  apr_hash_t *prop_hash = NULL;
  apr_hash_index_t *hi;
  const char *target_full_url =
    svn_path_url_add_component2(target_prefix, target_relative, scratch_pool);
  apr_array_header_t *inherited_props;

  /* Note that we pass only the SCRATCH_POOL to svn_ra_get[dir*|file*] because
     we'll be filtering out non-regular properties from PROP_HASH before we
     return. */
  if (kind == svn_node_dir)
    {
      SVN_ERR(svn_ra_get_dir2(ra_session,
                              (depth > svn_depth_empty) ? &dirents : NULL,
                              NULL, &prop_hash, target_relative, revnum,
                              SVN_DIRENT_KIND, scratch_pool));
    }
  else if (kind == svn_node_file)
    {
      SVN_ERR(svn_ra_get_file(ra_session, target_relative, revnum,
                              NULL, NULL, &prop_hash, scratch_pool));
    }
  else
    {
      return svn_error_createf(SVN_ERR_NODE_UNKNOWN_KIND, NULL,
                               _("Unknown node kind for '%s'"),
                               target_full_url);
    }

  if (get_target_inherited_props)
    {
      const char *repos_root_url;

      SVN_ERR(svn_ra_get_inherited_props(ra_session, &inherited_props,
                                         target_relative, revnum,
                                         scratch_pool, scratch_pool));
      SVN_ERR(svn_ra_get_repos_root2(ra_session, &repos_root_url,
                                     scratch_pool));
      SVN_ERR(svn_client__iprop_relpaths_to_urls(inherited_props,
                                                 repos_root_url,
                                                 scratch_pool,
                                                 scratch_pool));
    }
  else
    {
      inherited_props = NULL;
    }

  if (!get_explicit_props)
    prop_hash = NULL;
  else
    {
      /* Filter out non-regular properties, since the RA layer returns all
         kinds.  Copy regular properties keys/vals from the prop_hash
         allocated in SCRATCH_POOL to the "final" hash allocated in
         RESULT_POOL. */
      for (hi = apr_hash_first(scratch_pool, prop_hash);
           hi;
           hi = apr_hash_next(hi))
        {
          const char *name = apr_hash_this_key(hi);
          apr_ssize_t klen = apr_hash_this_key_len(hi);
          svn_prop_kind_t prop_kind;

          prop_kind = svn_property_kind2(name);

          if (prop_kind != svn_prop_regular_kind)
            {
              apr_hash_set(prop_hash, name, klen, NULL);
            }
        }
    }

  SVN_ERR(call_receiver(target_full_url, prop_hash, inherited_props,
                        receiver, receiver_baton, scratch_pool));

  if (depth > svn_depth_empty
      && get_explicit_props
      && (kind == svn_node_dir) && (apr_hash_count(dirents) > 0))
    {
      apr_pool_t *iterpool = svn_pool_create(scratch_pool);

      for (hi = apr_hash_first(scratch_pool, dirents);
           hi;
           hi = apr_hash_next(hi))
        {
          const char *this_name = apr_hash_this_key(hi);
          svn_dirent_t *this_ent = apr_hash_this_val(hi);
          const char *new_target_relative;

          if (cancel_func)
            SVN_ERR(cancel_func(cancel_baton));

          svn_pool_clear(iterpool);

          new_target_relative = svn_relpath_join(target_relative,
                                                 this_name, iterpool);

          if (this_ent->kind == svn_node_file
              || depth > svn_depth_files)
            {
              svn_depth_t depth_below_here = depth;

              if (depth == svn_depth_immediates)
                depth_below_here = svn_depth_empty;

              SVN_ERR(remote_proplist(target_prefix,
                                      new_target_relative,
                                      this_ent->kind,
                                      revnum,
                                      ra_session,
                                      TRUE /* get_explicit_props */,
                                      FALSE /* get_target_inherited_props */,
                                      depth_below_here,
                                      receiver, receiver_baton,
                                      cancel_func, cancel_baton,
                                      iterpool));
            }
        }

      svn_pool_destroy(iterpool);
    }

  return SVN_NO_ERROR;
}