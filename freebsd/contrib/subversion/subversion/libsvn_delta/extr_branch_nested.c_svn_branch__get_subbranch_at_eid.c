#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {TYPE_1__* payload; } ;
typedef  TYPE_2__ svn_element__content_t ;
struct TYPE_12__ {int /*<<< orphan*/  txn; } ;
typedef  TYPE_3__ svn_branch__state_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_10__ {scalar_t__ is_subbranch_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* svn_branch__get_id (TYPE_3__*,int /*<<< orphan*/ *) ; 
 char* svn_branch__id_nest (char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_branch__state_get_element (TYPE_3__*,TYPE_2__**,int,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_branch__txn_get_branch_by_id (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_branch__get_subbranch_at_eid(svn_branch__state_t *branch,
                                 svn_branch__state_t **subbranch_p,
                                 int eid,
                                 apr_pool_t *scratch_pool)
{
  svn_element__content_t *element;

  SVN_ERR(svn_branch__state_get_element(branch, &element, eid, scratch_pool));
  if (element && element->payload->is_subbranch_root)
    {
      const char *branch_id = svn_branch__get_id(branch, scratch_pool);
      const char *subbranch_id = svn_branch__id_nest(branch_id, eid,
                                                     scratch_pool);

      *subbranch_p = svn_branch__txn_get_branch_by_id(branch->txn, subbranch_id,
                                                      scratch_pool);
    }
  else
    {
      *subbranch_p = NULL;
    }
  return SVN_NO_ERROR;
}