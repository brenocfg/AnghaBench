#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int has_write_lock; int revprop_generation; } ;
typedef  TYPE_1__ svn_fs_x__data_t ;
struct TYPE_7__ {TYPE_1__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  read_revprop_generation (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_revprop_generation_file (TYPE_2__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
begin_revprop_change(svn_fs_t *fs,
                     apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  SVN_ERR_ASSERT(ffd->has_write_lock);

  /* Set the revprop generation to an odd value to indicate
   * that a write is in progress.
   */
  SVN_ERR(read_revprop_generation(fs, scratch_pool));
  ++ffd->revprop_generation;
  SVN_ERR_ASSERT(ffd->revprop_generation % 2);
  SVN_ERR(write_revprop_generation_file(fs, ffd->revprop_generation,
                                        scratch_pool));

  return SVN_NO_ERROR;
}