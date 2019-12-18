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
typedef  int /*<<< orphan*/  svn_error_t ;
struct recursive_propget_receiver_baton {int /*<<< orphan*/  pool; int /*<<< orphan*/  props; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_string_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
recursive_propget_receiver(void *baton,
                           const char *local_abspath,
                           apr_hash_t *props,
                           apr_pool_t *scratch_pool)
{
  struct recursive_propget_receiver_baton *b = baton;

  if (apr_hash_count(props))
    {
      apr_hash_index_t *hi = apr_hash_first(scratch_pool, props);
      svn_hash_sets(b->props, apr_pstrdup(b->pool, local_abspath),
                    svn_string_dup(apr_hash_this_val(hi), b->pool));
    }

  return SVN_NO_ERROR;
}