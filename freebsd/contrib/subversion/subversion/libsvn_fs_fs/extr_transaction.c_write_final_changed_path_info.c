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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_4__ {int /*<<< orphan*/  number; int /*<<< orphan*/  revision; } ;
struct TYPE_5__ {void* offset; int /*<<< orphan*/  fnv1_checksum; TYPE_1__ item; int /*<<< orphan*/  type; void* size; } ;
typedef  TYPE_2__ svn_fs_fs__p2l_entry_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  void* apr_off_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_FS_FS__ITEM_INDEX_CHANGES ; 
 int /*<<< orphan*/  SVN_FS_FS__ITEM_TYPE_CHANGES ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fnv1a_checksum_finalize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnv1a_wrap_stream (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_l2p_index_entry (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  store_p2l_index_entry (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_fs__use_log_addressing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__write_changes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_file_get_offset (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_from_aprfile2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
write_final_changed_path_info(apr_off_t *offset_p,
                              apr_file_t *file,
                              svn_fs_t *fs,
                              const svn_fs_fs__id_part_t *txn_id,
                              apr_hash_t *changed_paths,
                              apr_pool_t *pool)
{
  apr_off_t offset;
  svn_stream_t *stream;
  svn_checksum_ctx_t *fnv1a_checksum_ctx;

  SVN_ERR(svn_io_file_get_offset(&offset, file, pool));

  /* write to target file & calculate checksum if needed */
  stream = svn_stream_from_aprfile2(file, TRUE, pool);
  if (svn_fs_fs__use_log_addressing(fs))
    stream = fnv1a_wrap_stream(&fnv1a_checksum_ctx, stream, pool);
  else
    fnv1a_checksum_ctx = NULL;

  SVN_ERR(svn_fs_fs__write_changes(stream, fs, changed_paths, TRUE, pool));

  *offset_p = offset;

  /* reference changes from the indexes */
  if (svn_fs_fs__use_log_addressing(fs))
    {
      svn_fs_fs__p2l_entry_t entry;

      entry.offset = offset;
      SVN_ERR(svn_io_file_get_offset(&offset, file, pool));
      entry.size = offset - entry.offset;
      entry.type = SVN_FS_FS__ITEM_TYPE_CHANGES;
      entry.item.revision = SVN_INVALID_REVNUM;
      entry.item.number = SVN_FS_FS__ITEM_INDEX_CHANGES;
      SVN_ERR(fnv1a_checksum_finalize(&entry.fnv1_checksum,
                                      fnv1a_checksum_ctx,
                                      pool));

      SVN_ERR(store_p2l_index_entry(fs, txn_id, &entry, pool));
      SVN_ERR(store_l2p_index_entry(fs, txn_id, entry.offset,
                                    SVN_FS_FS__ITEM_INDEX_CHANGES, pool));
    }

  return SVN_NO_ERROR;
}