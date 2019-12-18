#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ changed_paths2; scalar_t__ changed_paths; scalar_t__ revprops; } ;
typedef  TYPE_1__ svn_log_entry_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,void const**,int /*<<< orphan*/ *,void**) ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,void const*) ; 
 int /*<<< orphan*/  svn_hash_sets (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_log_changed_path2_dup (void*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_prop_hash_dup (scalar_t__,int /*<<< orphan*/ *) ; 

svn_log_entry_t *
svn_log_entry_dup(const svn_log_entry_t *log_entry, apr_pool_t *pool)
{
  apr_hash_index_t *hi;
  svn_log_entry_t *new_entry = apr_palloc(pool, sizeof(*new_entry));

  *new_entry = *log_entry;

  if (log_entry->revprops)
    new_entry->revprops = svn_prop_hash_dup(log_entry->revprops, pool);

  if (log_entry->changed_paths2)
    {
      new_entry->changed_paths2 = apr_hash_make(pool);

      for (hi = apr_hash_first(pool, log_entry->changed_paths2);
           hi; hi = apr_hash_next(hi))
        {
          const void *key;
          void *change;

          apr_hash_this(hi, &key, NULL, &change);

          svn_hash_sets(new_entry->changed_paths2, apr_pstrdup(pool, key),
                        svn_log_changed_path2_dup(change, pool));
        }
    }

  /* We can't copy changed_paths by itself without using deprecated code,
     but we don't have to, as this function was new after the introduction
     of the changed_paths2 field. */
  new_entry->changed_paths = new_entry->changed_paths2;

  return new_entry;
}