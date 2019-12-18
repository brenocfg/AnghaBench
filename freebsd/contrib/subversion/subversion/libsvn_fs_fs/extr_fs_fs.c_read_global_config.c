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
struct TYPE_4__ {int /*<<< orphan*/  config; TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {int flush_to_disk; int /*<<< orphan*/  block_size; scalar_t__ use_block_read; } ;
typedef  TYPE_2__ fs_fs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_FSFS_BLOCK_READ ; 
 int /*<<< orphan*/  SVN_FS_CONFIG_NO_FLUSH_TO_DISK ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ svn_hash__get_bool (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
read_global_config(svn_fs_t *fs)
{
  fs_fs_data_t *ffd = fs->fsap_data;

  ffd->use_block_read = svn_hash__get_bool(fs->config,
                                           SVN_FS_CONFIG_FSFS_BLOCK_READ,
                                           FALSE);
  ffd->flush_to_disk = !svn_hash__get_bool(fs->config,
                                           SVN_FS_CONFIG_NO_FLUSH_TO_DISK,
                                           FALSE);

  /* Ignore the user-specified larger block size if we don't use block-read.
     Defaulting to 4k gives us the same access granularity in format 7 as in
     older formats. */
  if (!ffd->use_block_read)
    ffd->block_size = MIN(0x1000, ffd->block_size);

  return SVN_NO_ERROR;
}