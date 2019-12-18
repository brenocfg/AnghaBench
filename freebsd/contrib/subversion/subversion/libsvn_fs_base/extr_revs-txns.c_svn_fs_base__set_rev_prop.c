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
struct TYPE_4__ {scalar_t__ proplist; } ;
typedef  TYPE_1__ transaction_t ;
typedef  int /*<<< orphan*/  trail_t ;
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_PROP_BASEVALUE_MISMATCH ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_rev_txn (TYPE_1__**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * put_txn (int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * svn_hash_gets (scalar_t__,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (scalar_t__,char const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ svn_string_compare (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

svn_error_t *
svn_fs_base__set_rev_prop(svn_fs_t *fs,
                          svn_revnum_t rev,
                          const char *name,
                          const svn_string_t *const *old_value_p,
                          const svn_string_t *value,
                          trail_t *trail,
                          apr_pool_t *pool)
{
  transaction_t *txn;
  const char *txn_id;
  const svn_string_t *present_value;

  SVN_ERR(get_rev_txn(&txn, &txn_id, fs, rev, trail, pool));
  present_value = svn_hash_gets(txn->proplist, name);

  /* If there's no proplist, but we're just deleting a property, exit now. */
  if ((! txn->proplist) && (! value))
    return SVN_NO_ERROR;

  /* Now, if there's no proplist, we know we need to make one. */
  if (! txn->proplist)
    txn->proplist = apr_hash_make(pool);

  /* Set the property. */
  if (old_value_p)
    {
      const svn_string_t *wanted_value = *old_value_p;
      if ((!wanted_value != !present_value)
          || (wanted_value && present_value
              && !svn_string_compare(wanted_value, present_value)))
        {
          /* What we expected isn't what we found. */
          return svn_error_createf(SVN_ERR_FS_PROP_BASEVALUE_MISMATCH, NULL,
                                   _("revprop '%s' has unexpected value in "
                                     "filesystem"),
                                   name);
        }
      /* Fall through. */
    }

  /* If the prop-set is a no-op, skip the actual write. */
  if ((!present_value && !value)
      || (present_value && value
          && svn_string_compare(present_value, value)))
    return SVN_NO_ERROR;

  svn_hash_sets(txn->proplist, name, value);

  /* Overwrite the revision. */
  return put_txn(fs, txn, txn_id, trail, pool);
}