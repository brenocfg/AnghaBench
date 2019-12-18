#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/ * legacy_tree_conflict; scalar_t__ prop_conflicts; int /*<<< orphan*/ * legacy_text_conflict; } ;
typedef  TYPE_1__ svn_client_conflict_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_array_make (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svn_hash_keys (int /*<<< orphan*/ **,scalar_t__,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client_conflict_get_conflicted(svn_boolean_t *text_conflicted,
                                   apr_array_header_t **props_conflicted,
                                   svn_boolean_t *tree_conflicted,
                                   svn_client_conflict_t *conflict,
                                   apr_pool_t *result_pool,
                                   apr_pool_t *scratch_pool)
{
  if (text_conflicted)
    *text_conflicted = (conflict->legacy_text_conflict != NULL);

  if (props_conflicted)
    {
      if (conflict->prop_conflicts)
        SVN_ERR(svn_hash_keys(props_conflicted, conflict->prop_conflicts,
                              result_pool));
      else
        *props_conflicted = apr_array_make(result_pool, 0,
                                           sizeof(const char*));
    }

  if (tree_conflicted)
    *tree_conflicted = (conflict->legacy_tree_conflict != NULL);

  return SVN_NO_ERROR;
}