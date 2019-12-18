#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ revprops; } ;
typedef  TYPE_1__ svn_repos_log_entry_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pmemdup (int /*<<< orphan*/ *,TYPE_1__ const*,int) ; 
 scalar_t__ svn_prop_hash_dup (scalar_t__,int /*<<< orphan*/ *) ; 

svn_repos_log_entry_t *
svn_repos_log_entry_dup(const svn_repos_log_entry_t *log_entry,
                        apr_pool_t *result_pool)
{
  svn_repos_log_entry_t *new_entry = apr_pmemdup(result_pool, log_entry,
                                                sizeof(*new_entry));

  if (log_entry->revprops)
    new_entry->revprops = svn_prop_hash_dup(log_entry->revprops, result_pool);

  return new_entry;
}