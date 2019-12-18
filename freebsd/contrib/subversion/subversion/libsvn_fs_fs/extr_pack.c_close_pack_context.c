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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  pack_file; scalar_t__ flush_to_disk; int /*<<< orphan*/  shard_rev; int /*<<< orphan*/  fs; int /*<<< orphan*/  proto_p2l_index; int /*<<< orphan*/  proto_l2p_index; } ;
typedef  TYPE_1__ pack_context_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_fs__add_index_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_flush_to_disk (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_name_get (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_remove_file2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
close_pack_context(pack_context_t *context,
                   apr_pool_t *pool)
{
  const char *proto_l2p_index_path;
  const char *proto_p2l_index_path;

  /* need the file names for the actual index creation call further down */
  SVN_ERR(svn_io_file_name_get(&proto_l2p_index_path,
                               context->proto_l2p_index, pool));
  SVN_ERR(svn_io_file_name_get(&proto_p2l_index_path,
                               context->proto_p2l_index, pool));

  /* finalize proto index files */
  SVN_ERR(svn_io_file_close(context->proto_l2p_index, pool));
  SVN_ERR(svn_io_file_close(context->proto_p2l_index, pool));

  /* Append the actual index data to the pack file. */
  SVN_ERR(svn_fs_fs__add_index_data(context->fs, context->pack_file,
                                    proto_l2p_index_path,
                                    proto_p2l_index_path,
                                    context->shard_rev,
                                    pool));

  /* remove proto index files */
  SVN_ERR(svn_io_remove_file2(proto_l2p_index_path, FALSE, pool));
  SVN_ERR(svn_io_remove_file2(proto_p2l_index_path, FALSE, pool));

  /* Ensure that packed file is written to disk.*/
  if (context->flush_to_disk)
    SVN_ERR(svn_io_file_flush_to_disk(context->pack_file, pool));
  SVN_ERR(svn_io_file_close(context->pack_file, pool));

  return SVN_NO_ERROR;
}