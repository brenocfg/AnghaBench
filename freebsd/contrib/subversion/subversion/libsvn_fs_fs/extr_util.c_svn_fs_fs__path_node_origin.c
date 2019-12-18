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
struct TYPE_5__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ svn_fs_t ;
struct TYPE_6__ {int /*<<< orphan*/  number; } ;
typedef  TYPE_2__ svn_fs_fs__id_part_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_NODE_ORIGINS_DIR ; 
 int SVN_INT64_BUFFER_SIZE ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int svn__ui64tobase36 (char*,int /*<<< orphan*/ ) ; 
 char const* svn_dirent_join_many (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

const char *
svn_fs_fs__path_node_origin(svn_fs_t *fs,
                            const svn_fs_fs__id_part_t *node_id,
                            apr_pool_t *pool)
{
  char buffer[SVN_INT64_BUFFER_SIZE];
  apr_size_t len = svn__ui64tobase36(buffer, node_id->number);

  if (len > 1)
    buffer[len - 1] = '\0';

  return svn_dirent_join_many(pool, fs->path, PATH_NODE_ORIGINS_DIR,
                              buffer, SVN_VA_NULL);
}