#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flush_to_disk; } ;
typedef  TYPE_1__ svn_fs_x__data_t ;
struct TYPE_5__ {int /*<<< orphan*/  config; TYPE_1__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_NO_FLUSH_TO_DISK ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_hash__get_bool (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
read_global_config(svn_fs_t *fs)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;

  ffd->flush_to_disk = !svn_hash__get_bool(fs->config,
                                           SVN_FS_CONFIG_NO_FLUSH_TO_DISK,
                                           FALSE);

  return SVN_NO_ERROR;
}