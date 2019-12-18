#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_INT64_BUFFER_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 char const* construct_shard_sub_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn__i64toa (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__is_packed_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

const char *
svn_fs_x__path_rev(svn_fs_t *fs,
                   svn_revnum_t rev,
                   apr_pool_t *result_pool)
{
  char buffer[SVN_INT64_BUFFER_SIZE + 1];
  buffer[0] = 'r';
  svn__i64toa(buffer + 1, rev);

  assert(! svn_fs_x__is_packed_rev(fs, rev));
  return construct_shard_sub_path(fs, rev, FALSE, buffer, result_pool);
}