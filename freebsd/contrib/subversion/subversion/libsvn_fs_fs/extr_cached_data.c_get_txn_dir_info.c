#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  filesize; } ;
typedef  TYPE_2__ svn_io_dirent2_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {int /*<<< orphan*/  id; TYPE_1__* data_rep; } ;
typedef  TYPE_3__ node_revision_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {int /*<<< orphan*/  txn_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_FILESIZE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ svn_fs_fs__id_txn_used (int /*<<< orphan*/ *) ; 
 char* svn_fs_fs__path_txn_node_children (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_stat_dirent2 (TYPE_2__ const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_txn_dir_info(svn_filesize_t *filesize,
                 svn_fs_t *fs,
                 node_revision_t *noderev,
                 apr_pool_t *scratch_pool)
{
  if (noderev->data_rep && svn_fs_fs__id_txn_used(&noderev->data_rep->txn_id))
    {
      const svn_io_dirent2_t *dirent;
      const char *filename;

      filename = svn_fs_fs__path_txn_node_children(fs, noderev->id,
                                                   scratch_pool);

      SVN_ERR(svn_io_stat_dirent2(&dirent, filename, FALSE, FALSE,
                                  scratch_pool, scratch_pool));
      *filesize = dirent->filesize;
    }
  else
    {
      *filesize = SVN_INVALID_FILESIZE;
    }

  return SVN_NO_ERROR;
}