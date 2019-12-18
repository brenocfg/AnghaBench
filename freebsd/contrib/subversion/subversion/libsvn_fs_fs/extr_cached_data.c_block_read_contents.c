#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_11__ {int /*<<< orphan*/  stream; } ;
typedef  TYPE_2__ svn_fs_fs__revision_file_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__rep_header_t ;
struct TYPE_10__ {int /*<<< orphan*/  number; scalar_t__ revision; } ;
struct TYPE_12__ {TYPE_1__ item; } ;
typedef  TYPE_3__ svn_fs_fs__p2l_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_13__ {int /*<<< orphan*/  second; scalar_t__ revision; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ pair_cache_key_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;
typedef  scalar_t__ apr_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  block_read_windows (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_rep_header (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
block_read_contents(svn_fs_t *fs,
                    svn_fs_fs__revision_file_t *rev_file,
                    svn_fs_fs__p2l_entry_t* entry,
                    apr_off_t max_offset,
                    apr_pool_t *scratch_pool)
{
  pair_cache_key_t header_key = { 0 };
  svn_fs_fs__rep_header_t *rep_header;

  header_key.revision = (apr_int32_t)entry->item.revision;
  header_key.second = entry->item.number;

  SVN_ERR(read_rep_header(&rep_header, fs, rev_file->stream, &header_key,
                          scratch_pool, scratch_pool));
  SVN_ERR(block_read_windows(rep_header, fs, rev_file, entry, max_offset,
                             scratch_pool, scratch_pool));

  return SVN_NO_ERROR;
}