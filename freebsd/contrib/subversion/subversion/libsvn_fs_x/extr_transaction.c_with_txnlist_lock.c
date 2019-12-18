#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  txn_list_lock; } ;
typedef  TYPE_1__ svn_fs_x__shared_data_t ;
struct TYPE_8__ {TYPE_1__* shared; } ;
typedef  TYPE_2__ svn_fs_x__data_t ;
struct TYPE_9__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_3__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_MUTEX__WITH_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 

__attribute__((used)) static svn_error_t *
with_txnlist_lock(svn_fs_t *fs,
                  svn_error_t *(*body)(svn_fs_t *fs,
                                       const void *baton,
                                       apr_pool_t *pool),
                  const void *baton,
                  apr_pool_t *pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  svn_fs_x__shared_data_t *ffsd = ffd->shared;

  SVN_MUTEX__WITH_LOCK(ffsd->txn_list_lock,
                       body(fs, baton, pool));

  return SVN_NO_ERROR;
}