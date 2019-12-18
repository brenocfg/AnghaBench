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
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct getter_baton {char const* local_abspath; int /*<<< orphan*/  const* mime_type; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char const* SVN_PROP_MIME_TYPE ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ensure_prop_is_regular_kind (char const*) ; 
 int /*<<< orphan*/ * get_file_for_validation ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svn_wc_canonicalize_svn_prop (int /*<<< orphan*/  const**,char const*,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct getter_baton*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__canonicalize_props(apr_hash_t **prepared_props,
                           const char *local_abspath,
                           svn_node_kind_t node_kind,
                           const apr_hash_t *props,
                           svn_boolean_t skip_some_checks,
                           apr_pool_t *result_pool,
                           apr_pool_t *scratch_pool)
{
  const svn_string_t *mime_type;
  struct getter_baton gb;
  apr_hash_index_t *hi;

  /* While we allocate new parts of *PREPARED_PROPS in RESULT_POOL, we
     don't promise to deep-copy the unchanged keys and values. */
  *prepared_props = apr_hash_make(result_pool);

  /* Before we can canonicalize svn:eol-style we need to know svn:mime-type,
   * so process that first. */
  mime_type = svn_hash_gets((apr_hash_t *)props, SVN_PROP_MIME_TYPE);
  if (mime_type)
    {
      SVN_ERR(svn_wc_canonicalize_svn_prop(
                &mime_type, SVN_PROP_MIME_TYPE, mime_type,
                local_abspath, node_kind, skip_some_checks,
                NULL, NULL, scratch_pool));
      svn_hash_sets(*prepared_props, SVN_PROP_MIME_TYPE, mime_type);
    }

  /* Set up the context for canonicalizing the other properties. */
  gb.mime_type = mime_type;
  gb.local_abspath = local_abspath;

  /* Check and canonicalize the other properties. */
  for (hi = apr_hash_first(scratch_pool, (apr_hash_t *)props); hi;
       hi = apr_hash_next(hi))
    {
      const char *name = apr_hash_this_key(hi);
      const svn_string_t *value = apr_hash_this_val(hi);

      if (strcmp(name, SVN_PROP_MIME_TYPE) == 0)
        continue;

      SVN_ERR(ensure_prop_is_regular_kind(name));
      SVN_ERR(svn_wc_canonicalize_svn_prop(
                &value, name, value,
                local_abspath, node_kind, skip_some_checks,
                get_file_for_validation, &gb, scratch_pool));
      svn_hash_sets(*prepared_props, name, value);
    }

  return SVN_NO_ERROR;
}