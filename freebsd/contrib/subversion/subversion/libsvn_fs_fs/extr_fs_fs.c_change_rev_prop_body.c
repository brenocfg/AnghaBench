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
struct change_rev_prop_baton {int /*<<< orphan*/  rev; int /*<<< orphan*/  fs; int /*<<< orphan*/  const* value; int /*<<< orphan*/  name; int /*<<< orphan*/ ** old_value_p; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_PROP_BASEVALUE_MISMATCH ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__get_revision_proplist (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_fs_fs__set_revision_proplist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ svn_string_compare (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static svn_error_t *
change_rev_prop_body(void *baton, apr_pool_t *pool)
{
  struct change_rev_prop_baton *cb = baton;
  apr_hash_t *table;
  const svn_string_t *present_value;

  /* We always need to read the current revprops from disk.
   * Hence, always "refresh" here. */
  SVN_ERR(svn_fs_fs__get_revision_proplist(&table, cb->fs, cb->rev, TRUE,
                                           pool, pool));
  present_value = svn_hash_gets(table, cb->name);

  if (cb->old_value_p)
    {
      const svn_string_t *wanted_value = *cb->old_value_p;
      if ((!wanted_value != !present_value)
          || (wanted_value && present_value
              && !svn_string_compare(wanted_value, present_value)))
        {
          /* What we expected isn't what we found. */
          return svn_error_createf(SVN_ERR_FS_PROP_BASEVALUE_MISMATCH, NULL,
                                   _("revprop '%s' has unexpected value in "
                                     "filesystem"),
                                   cb->name);
        }
      /* Fall through. */
    }

  /* If the prop-set is a no-op, skip the actual write. */
  if ((!present_value && !cb->value)
      || (present_value && cb->value
          && svn_string_compare(present_value, cb->value)))
    return SVN_NO_ERROR;

  svn_hash_sets(table, cb->name, cb->value);

  return svn_fs_fs__set_revision_proplist(cb->fs, cb->rev, table, pool);
}