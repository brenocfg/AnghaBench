#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_x__revision_file_t ;
struct TYPE_6__ {int /*<<< orphan*/  change_set; } ;
struct TYPE_5__ {TYPE_3__ id; } ;
typedef  TYPE_1__ svn_fs_x__representation_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * open_and_seek_revision (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * open_and_seek_transaction (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_x__is_revision (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
open_and_seek_representation(svn_fs_x__revision_file_t **file_p,
                             svn_fs_t *fs,
                             svn_fs_x__representation_t *rep,
                             apr_pool_t *result_pool,
                             apr_pool_t *scratch_pool)
{
  if (svn_fs_x__is_revision(rep->id.change_set))
    return open_and_seek_revision(file_p, fs, &rep->id, result_pool,
                                  scratch_pool);
  else
    return open_and_seek_transaction(file_p, fs, rep, result_pool,
                                     scratch_pool);
}