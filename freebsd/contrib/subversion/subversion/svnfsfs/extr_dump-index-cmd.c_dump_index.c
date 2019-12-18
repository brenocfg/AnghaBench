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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  check_cancel ; 
 int /*<<< orphan*/  dump_index_entry ; 
 int /*<<< orphan*/  open_fs (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  svn_fs_fs__dump_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
dump_index(const char *path,
           svn_revnum_t revision,
           apr_pool_t *pool)
{
  svn_fs_t *fs;

  /* Check repository type and open it. */
  SVN_ERR(open_fs(&fs, path, pool));

  /* Write header line. */
  printf("       Start       Length Type   Revision     Item Checksum\n");

  /* Dump the whole index contents */
  SVN_ERR(svn_fs_fs__dump_index(fs, revision, dump_index_entry, NULL,
                                check_cancel, NULL, pool));

  return SVN_NO_ERROR;
}