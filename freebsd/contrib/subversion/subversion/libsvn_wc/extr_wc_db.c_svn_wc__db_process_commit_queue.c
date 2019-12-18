#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc__db_t ;
struct TYPE_4__ {int /*<<< orphan*/  wcroot; } ;
typedef  TYPE_1__ svn_wc__db_commit_queue_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__DB_WITH_TXN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_process_commit_queue (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_process_commit_queue(svn_wc__db_t *db,
                                svn_wc__db_commit_queue_t *queue,
                                svn_revnum_t new_revnum,
                                apr_time_t new_date,
                                const char *new_author,
                                apr_pool_t *scratch_pool)
{
  SVN_WC__DB_WITH_TXN(db_process_commit_queue(db, queue,
                                              new_revnum, new_date,
                                              new_author, scratch_pool),
                        queue->wcroot);

  return SVN_NO_ERROR;
}