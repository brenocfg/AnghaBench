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
struct TYPE_5__ {int /*<<< orphan*/  uuid; TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {scalar_t__ format; scalar_t__ max_files_per_dir; } ;
typedef  TYPE_2__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_RA_UUID_MISMATCH ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static svn_error_t *
hotcopy_incremental_check_preconditions(svn_fs_t *src_fs,
                                        svn_fs_t *dst_fs,
                                        apr_pool_t *pool)
{
  fs_fs_data_t *src_ffd = src_fs->fsap_data;
  fs_fs_data_t *dst_ffd = dst_fs->fsap_data;

  /* We only support incremental hotcopy between the same format. */
  if (src_ffd->format != dst_ffd->format)
    return svn_error_createf(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
      _("The FSFS format (%d) of the hotcopy source does not match the "
        "FSFS format (%d) of the hotcopy destination; please upgrade "
        "both repositories to the same format"),
      src_ffd->format, dst_ffd->format);

  /* Make sure the UUID of source and destination match up.
   * We don't want to copy over a different repository. */
  if (strcmp(src_fs->uuid, dst_fs->uuid) != 0)
    return svn_error_create(SVN_ERR_RA_UUID_MISMATCH, NULL,
                            _("The UUID of the hotcopy source does "
                              "not match the UUID of the hotcopy "
                              "destination"));

  /* Also require same shard size. */
  if (src_ffd->max_files_per_dir != dst_ffd->max_files_per_dir)
    return svn_error_create(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                            _("The sharding layout configuration "
                              "of the hotcopy source does not match "
                              "the sharding layout configuration of "
                              "the hotcopy destination"));
  return SVN_NO_ERROR;
}