#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_17__ {TYPE_6__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__revision_file_t ;
struct TYPE_16__ {int /*<<< orphan*/  revision; } ;
struct TYPE_18__ {int /*<<< orphan*/  size; TYPE_1__ item; } ;
typedef  TYPE_3__ svn_fs_fs__p2l_entry_t ;
struct TYPE_19__ {scalar_t__ count; int /*<<< orphan*/  eol; int /*<<< orphan*/ ** changes; scalar_t__ start_offset; int /*<<< orphan*/  end_offset; } ;
typedef  TYPE_4__ svn_fs_fs__changes_list_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_20__ {scalar_t__ second; int /*<<< orphan*/  revision; } ;
typedef  TYPE_5__ pair_cache_key_t ;
struct TYPE_21__ {scalar_t__ changes_cache; } ;
typedef  TYPE_6__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  change_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_22__ {scalar_t__ nelts; scalar_t__ elts; } ;
typedef  TYPE_7__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_FS_FS__CHANGES_BLOCK_SIZE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  read_item (int /*<<< orphan*/ **,TYPE_2__*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__has_key (scalar_t__*,scalar_t__,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__set (scalar_t__,TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__read_changes (TYPE_7__**,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
block_read_changes(svn_fs_t *fs,
                   svn_fs_fs__revision_file_t *rev_file,
                   svn_fs_fs__p2l_entry_t *entry,
                   apr_pool_t *scratch_pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;
  svn_stream_t *stream;
  apr_array_header_t *changes;

  pair_cache_key_t key;
  key.revision = entry->item.revision;
  key.second = 0;

  if (!ffd->changes_cache)
    return SVN_NO_ERROR;

  /* already in cache? */
  if (ffd->changes_cache)
    {
      svn_boolean_t is_cached;
      SVN_ERR(svn_cache__has_key(&is_cached, ffd->changes_cache, &key,
                                 scratch_pool));
      if (is_cached)
        return SVN_NO_ERROR;
    }

  SVN_ERR(read_item(&stream, fs, rev_file, entry, scratch_pool));

  /* Read changes from revision file.  But read just past the first block to
     enable us to determine whether the first block already hit the EOL.

     Note: A 100 entries block is already > 10kB on disk.  With a 4kB default
           disk block size, this function won't even be called for larger
           changed paths lists. */
  SVN_ERR(svn_fs_fs__read_changes(&changes, stream,
                                  SVN_FS_FS__CHANGES_BLOCK_SIZE + 1,
                                  scratch_pool, scratch_pool));

  /* We can only cache small lists that don't need to be split up.
     For longer lists, we miss the file offset info for the respective */
  if (changes->nelts <= SVN_FS_FS__CHANGES_BLOCK_SIZE)
    {
      svn_fs_fs__changes_list_t changes_list;

      /* Construct the info object for the entries block we just read. */
      changes_list.end_offset = entry->size;
      changes_list.start_offset = 0;
      changes_list.count = changes->nelts;
      changes_list.changes = (change_t **)changes->elts;
      changes_list.eol = TRUE;

      SVN_ERR(svn_cache__set(ffd->changes_cache, &key, &changes_list,
                             scratch_pool));
    }

  return SVN_NO_ERROR;
}