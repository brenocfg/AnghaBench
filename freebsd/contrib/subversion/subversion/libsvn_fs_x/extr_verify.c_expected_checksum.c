#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_x__revision_file_t ;
struct TYPE_3__ {scalar_t__ fnv1_checksum; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ svn_fs_x__p2l_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_off_t_toa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_name (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
expected_checksum(svn_fs_x__revision_file_t *file,
                  svn_fs_x__p2l_entry_t *entry,
                  apr_uint32_t actual,
                  apr_pool_t *scratch_pool)
{
  if (actual != entry->fnv1_checksum)
    {
      const char *file_name;

      SVN_ERR(svn_fs_x__rev_file_name(&file_name, file, scratch_pool));
      return svn_error_createf(SVN_ERR_FS_CORRUPT, NULL,
                               _("Checksum mismatch in item at offset %s of "
                                 "length %s bytes in file %s"),
                               apr_off_t_toa(scratch_pool, entry->offset),
                               apr_off_t_toa(scratch_pool, entry->size),
                               file_name);
    }

  return SVN_NO_ERROR;
}