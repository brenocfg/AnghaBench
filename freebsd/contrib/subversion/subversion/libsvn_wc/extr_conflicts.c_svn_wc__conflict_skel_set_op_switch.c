#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_conflict_version_t ;
struct TYPE_12__ {struct TYPE_12__* children; TYPE_1__* next; } ;
typedef  TYPE_2__ svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_11__ {int /*<<< orphan*/  is_atom; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__CONFLICT_OP_SWITCH ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  conflict__get_operation (TYPE_2__**,TYPE_2__*) ; 
 int /*<<< orphan*/  conflict__prepend_location (TYPE_2__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_skel__make_empty_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__prepend (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  svn_skel__prepend_str (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__conflict_skel_set_op_switch(svn_skel_t *conflict_skel,
                                    const svn_wc_conflict_version_t *original,
                                    const svn_wc_conflict_version_t *target,
                                    apr_pool_t *result_pool,
                                    apr_pool_t *scratch_pool)
{
  svn_skel_t *why;
  svn_skel_t *origins;

  SVN_ERR_ASSERT(conflict_skel
                 && conflict_skel->children
                 && conflict_skel->children->next
                 && !conflict_skel->children->next->is_atom);

  SVN_ERR(conflict__get_operation(&why, conflict_skel));

  SVN_ERR_ASSERT(why == NULL); /* No operation set */

  why = conflict_skel->children;

  origins = svn_skel__make_empty_list(result_pool);

  SVN_ERR(conflict__prepend_location(origins, target, TRUE,
                                     result_pool, scratch_pool));
  SVN_ERR(conflict__prepend_location(origins, original, TRUE,
                                     result_pool, scratch_pool));

  svn_skel__prepend(origins, why);
  svn_skel__prepend_str(SVN_WC__CONFLICT_OP_SWITCH, why, result_pool);

  return SVN_NO_ERROR;
}