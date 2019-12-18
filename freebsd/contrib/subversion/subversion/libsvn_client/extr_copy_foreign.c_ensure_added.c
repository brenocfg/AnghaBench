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
typedef  int /*<<< orphan*/  svn_error_t ;
struct dir_baton_t {TYPE_1__* eb; int /*<<< orphan*/  properties; int /*<<< orphan*/  local_abspath; scalar_t__ created; struct dir_baton_t* pb; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_2__ {int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  notify_func; int /*<<< orphan*/  wc_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/ * svn_wc_add_from_disk3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
ensure_added(struct dir_baton_t *db,
             apr_pool_t *scratch_pool)
{
  if (db->created)
    return SVN_NO_ERROR;

  if (db->pb)
    SVN_ERR(ensure_added(db->pb, scratch_pool));

  db->created = TRUE;

  /* Add the directory with all the already collected properties */
  SVN_ERR(svn_wc_add_from_disk3(db->eb->wc_ctx,
                                db->local_abspath,
                                db->properties,
                                TRUE /* skip checks */,
                                db->eb->notify_func,
                                db->eb->notify_baton,
                                scratch_pool));

  return SVN_NO_ERROR;
}