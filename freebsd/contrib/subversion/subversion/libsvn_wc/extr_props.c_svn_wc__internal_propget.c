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
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  enum svn_prop_kind { ____Placeholder_svn_prop_kind } svn_prop_kind ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_W (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int svn_prop_entry_kind ; 
 int svn_prop_wc_kind ; 
 int svn_property_kind2 (char const*) ; 
 int /*<<< orphan*/  svn_wc__db_base_get_dav_cache (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__get_actual_props (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__internal_propget(const svn_string_t **value,
                         svn_wc__db_t *db,
                         const char *local_abspath,
                         const char *name,
                         apr_pool_t *result_pool,
                         apr_pool_t *scratch_pool)
{
  apr_hash_t *prophash = NULL;
  enum svn_prop_kind kind = svn_property_kind2(name);

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));
  SVN_ERR_ASSERT(kind != svn_prop_entry_kind);

  if (kind == svn_prop_wc_kind)
    {
      SVN_ERR_W(svn_wc__db_base_get_dav_cache(&prophash, db, local_abspath,
                                              result_pool, scratch_pool),
                _("Failed to load properties"));
    }
  else
    {
      /* regular prop */
      SVN_ERR_W(svn_wc__get_actual_props(&prophash, db, local_abspath,
                                         result_pool, scratch_pool),
                _("Failed to load properties"));
    }

  if (prophash)
    *value = svn_hash_gets(prophash, name);
  else
    *value = NULL;

  return SVN_NO_ERROR;
}