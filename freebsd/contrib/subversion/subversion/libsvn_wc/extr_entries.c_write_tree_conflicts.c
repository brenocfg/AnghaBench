#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
struct TYPE_2__ {char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_skel__make_empty_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__prepend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_skel__unparse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__serialize_conflict (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
write_tree_conflicts(const char **conflict_data,
                     apr_hash_t *conflicts,
                     apr_pool_t *pool)
{
  svn_skel_t *skel = svn_skel__make_empty_list(pool);
  apr_hash_index_t *hi;

  for (hi = apr_hash_first(pool, conflicts); hi; hi = apr_hash_next(hi))
    {
      svn_skel_t *c_skel;

      SVN_ERR(svn_wc__serialize_conflict(&c_skel, apr_hash_this_val(hi),
                                         pool, pool));
      svn_skel__prepend(c_skel, skel);
    }

  *conflict_data = svn_skel__unparse(skel, pool)->data;

  return SVN_NO_ERROR;
}