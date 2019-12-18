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
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_PROPERTY_NAME ; 
 int /*<<< orphan*/  SVN_ERR_CL_ARG_PARSING_ERROR ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 char* apr_pstrndup (int /*<<< orphan*/ *,char const*,int) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_prop_name_is_valid (char const*) ; 
 int /*<<< orphan*/ * svn_string_create (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_string_create_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_utf_cstring_to_utf8 (char const**,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_opt_parse_revprop(apr_hash_t **revprop_table_p, const char *revprop_spec,
                      apr_pool_t *pool)
{
  const char *sep, *propname;
  svn_string_t *propval;

  if (! *revprop_spec)
    return svn_error_create(SVN_ERR_CL_ARG_PARSING_ERROR, NULL,
                            _("Revision property pair is empty"));

  if (! *revprop_table_p)
    *revprop_table_p = apr_hash_make(pool);

  sep = strchr(revprop_spec, '=');
  if (sep)
    {
      propname = apr_pstrndup(pool, revprop_spec, sep - revprop_spec);
      SVN_ERR(svn_utf_cstring_to_utf8(&propname, propname, pool));
      propval = svn_string_create(sep + 1, pool);
    }
  else
    {
      SVN_ERR(svn_utf_cstring_to_utf8(&propname, revprop_spec, pool));
      propval = svn_string_create_empty(pool);
    }

  if (!svn_prop_name_is_valid(propname))
    return svn_error_createf(SVN_ERR_CLIENT_PROPERTY_NAME, NULL,
                             _("'%s' is not a valid Subversion property name"),
                             propname);

  svn_hash_sets(*revprop_table_p, propname, propval);

  return SVN_NO_ERROR;
}