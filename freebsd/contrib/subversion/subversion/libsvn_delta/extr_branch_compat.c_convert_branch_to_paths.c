#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_14__ {int /*<<< orphan*/  e_map; } ;
typedef  TYPE_3__ svn_element__tree_t ;
struct TYPE_15__ {TYPE_1__* payload; } ;
typedef  TYPE_4__ svn_element__content_t ;
struct TYPE_16__ {TYPE_2__* txn; } ;
typedef  TYPE_5__ svn_branch__state_t ;
typedef  int /*<<< orphan*/  svn_branch__el_rev_id_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
struct TYPE_13__ {int /*<<< orphan*/  rev; } ;
struct TYPE_12__ {scalar_t__ is_subbranch_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 TYPE_4__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 char* branch_get_storage_rrpath_by_eid (TYPE_5__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_branch__el_rev_id_create (TYPE_5__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_branch__state_get_elements (TYPE_5__*,TYPE_3__**,int /*<<< orphan*/ *) ; 
 int svn_eid__hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
convert_branch_to_paths(apr_hash_t *paths,
                        svn_branch__state_t *branch,
                        apr_pool_t *result_pool,
                        apr_pool_t *scratch_pool)
{
  apr_hash_index_t *hi;
  svn_element__tree_t *elements;

  /* assert(branch is at a sequence point); */

  SVN_ERR(svn_branch__state_get_elements(branch, &elements, scratch_pool));
  for (hi = apr_hash_first(scratch_pool, elements->e_map);
       hi; hi = apr_hash_next(hi))
    {
      int eid = svn_eid__hash_this_key(hi);
      svn_element__content_t *element = apr_hash_this_val(hi);
      const char *rrpath
        = branch_get_storage_rrpath_by_eid(branch, eid, result_pool);
      svn_branch__el_rev_id_t *ba;

      /* A subbranch-root element carries no payload; the corresponding
         inner branch root element will provide the payload for this path. */
      if (element->payload->is_subbranch_root)
        continue;

      /* No other element should exist at this path, given that we avoid
         storing anything for a subbranch-root element. */
      SVN_ERR_ASSERT(! svn_hash_gets(paths, rrpath));

      /* Fill in the details. */
      ba = svn_branch__el_rev_id_create(branch, eid, branch->txn->rev,
                                        result_pool);
      svn_hash_sets(paths, rrpath, ba);
      /*SVN_DBG(("branch-to-path[%d]: b%s e%d -> %s",
               i, svn_branch__get_id(branch, scratch_pool), eid, rrpath));*/
    }
  return SVN_NO_ERROR;
}