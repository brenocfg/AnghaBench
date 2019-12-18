#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  rev; int /*<<< orphan*/  relpath; } ;
typedef  TYPE_2__ svn_pathrev_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_13__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  text; int /*<<< orphan*/  props; int /*<<< orphan*/  kind; } ;
typedef  TYPE_3__ svn_element__payload_t ;
struct TYPE_14__ {int /*<<< orphan*/  fetch_baton; int /*<<< orphan*/  (* fetch_func ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;TYPE_1__* txn; } ;
typedef  TYPE_4__ svn_branch__txn_priv_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_11__ {int /*<<< orphan*/  repos; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAYLOAD_IS_ONLY_BY_REFERENCE (TYPE_3__*) ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  payload_get_storage_pathrev (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int svn_element__payload_invariants (TYPE_3__*) ; 

__attribute__((used)) static svn_error_t *
payload_resolve(svn_element__payload_t *payload,
                svn_branch__txn_priv_t *eb,
                apr_pool_t *scratch_pool)
{
  svn_pathrev_t storage;

  SVN_ERR_ASSERT(svn_element__payload_invariants(payload));

  if (! PAYLOAD_IS_ONLY_BY_REFERENCE(payload))
    return SVN_NO_ERROR;

  SVN_ERR(payload_get_storage_pathrev(&storage, payload,
                                      eb->txn->repos,
                                      scratch_pool));

  SVN_ERR(eb->fetch_func(&payload->kind,
                         &payload->props,
                         &payload->text,
                         NULL,
                         eb->fetch_baton,
                         storage.relpath, storage.rev,
                         payload->pool, scratch_pool));

  SVN_ERR_ASSERT(svn_element__payload_invariants(payload));
  SVN_ERR_ASSERT(! PAYLOAD_IS_ONLY_BY_REFERENCE(payload));
  return SVN_NO_ERROR;
}