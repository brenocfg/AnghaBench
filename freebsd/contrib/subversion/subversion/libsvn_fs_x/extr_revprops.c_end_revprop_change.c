#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int has_write_lock; int revprop_generation; } ;
typedef  TYPE_1__ svn_fs_x__data_t ;
struct TYPE_6__ {TYPE_1__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  write_revprop_generation_file (TYPE_2__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
end_revprop_change(svn_fs_t *fs,
                   apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  SVN_ERR_ASSERT(ffd->has_write_lock);
  SVN_ERR_ASSERT(ffd->revprop_generation % 2);

  /* Set the revprop generation to an even value to indicate
   * that a write has been completed.  Since we held the write
   * lock, nobody else could have updated the file contents.
   */
  SVN_ERR(write_revprop_generation_file(fs, ffd->revprop_generation + 1,
                                        scratch_pool));

  return SVN_NO_ERROR;
}