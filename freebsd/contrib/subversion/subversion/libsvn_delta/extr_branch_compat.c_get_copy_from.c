#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  rev; int /*<<< orphan*/ * relpath; } ;
typedef  TYPE_3__ svn_pathrev_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {scalar_t__ branch_id; } ;
struct TYPE_14__ {TYPE_1__ branch_ref; } ;
typedef  TYPE_4__ svn_element__payload_t ;
struct TYPE_15__ {TYPE_2__* txn; } ;
typedef  TYPE_5__ svn_branch__txn_priv_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_12__ {int /*<<< orphan*/  repos; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  payload_get_storage_pathrev (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_copy_from(svn_pathrev_t *copyfrom_pathrev_p,
              svn_element__payload_t *final_payload,
              svn_branch__txn_priv_t *eb,
              apr_pool_t *result_pool)
{
  if (final_payload->branch_ref.branch_id)
    {
      SVN_ERR(payload_get_storage_pathrev(copyfrom_pathrev_p, final_payload,
                                          eb->txn->repos,
                                          result_pool));
    }
  else
    {
      copyfrom_pathrev_p->relpath = NULL;
      copyfrom_pathrev_p->rev = SVN_INVALID_REVNUM;
    }

  return SVN_NO_ERROR;
}