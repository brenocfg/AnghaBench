#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_fs_x__revision_file_t ;
struct TYPE_20__ {scalar_t__ second; int /*<<< orphan*/  revision; } ;
typedef  TYPE_2__ svn_fs_x__pair_cache_key_t ;
struct TYPE_21__ {int item_count; scalar_t__ offset; scalar_t__ size; TYPE_1__* items; } ;
typedef  TYPE_3__ svn_fs_x__p2l_entry_t ;
struct TYPE_22__ {int /*<<< orphan*/  changes_cache; } ;
typedef  TYPE_4__ svn_fs_x__data_t ;
struct TYPE_23__ {scalar_t__ end_offset; scalar_t__ count; int eol; int /*<<< orphan*/ ** changes; scalar_t__ start_offset; } ;
typedef  TYPE_5__ svn_fs_x__changes_list_t ;
struct TYPE_24__ {scalar_t__ next; scalar_t__ next_offset; int eol; } ;
typedef  TYPE_6__ svn_fs_x__changes_context_t ;
typedef  int /*<<< orphan*/  svn_fs_x__change_t ;
struct TYPE_25__ {TYPE_4__* fsap_data; } ;
typedef  TYPE_7__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_26__ {scalar_t__ nelts; scalar_t__ elts; } ;
typedef  TYPE_8__ apr_array_header_t ;
struct TYPE_19__ {int /*<<< orphan*/  change_set; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 scalar_t__ SVN_FS_X__CHANGES_BLOCK_SIZE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  read_item (int /*<<< orphan*/ **,TYPE_7__*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__has_key (scalar_t__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__set (int /*<<< orphan*/ ,TYPE_2__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__get_revnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__read_changes (TYPE_8__**,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_offset (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_stream (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
block_read_changes(apr_array_header_t **changes,
                   svn_fs_t *fs,
                   svn_fs_x__revision_file_t *rev_file,
                   svn_fs_x__p2l_entry_t* entry,
                   svn_fs_x__changes_context_t *context,
                   svn_boolean_t must_read,
                   apr_pool_t *result_pool,
                   apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  svn_stream_t *stream;
  svn_fs_x__pair_cache_key_t key;
  svn_fs_x__changes_list_t changes_list;

  /* If we don't have to return any data, just read and cache the first
     block.  This means we won't cache the remaining blocks from longer
     lists right away but only if they are actually needed. */
  apr_size_t next = must_read ? context->next : 0;
  apr_size_t next_offset = must_read ? context->next_offset : 0;

  /* we don't support containers, yet */
  SVN_ERR_ASSERT(entry->item_count == 1);

  /* The item to read / write. */
  key.revision = svn_fs_x__get_revnum(entry->items[0].change_set);
  key.second = next;

  /* already in cache? */
  if (!must_read)
    {
      svn_boolean_t is_cached = FALSE;
      SVN_ERR(svn_cache__has_key(&is_cached, ffd->changes_cache, &key,
                                 scratch_pool));
      if (is_cached)
        return SVN_NO_ERROR;
    }

  /* Verify the whole list only once.  We don't use the STREAM any further. */
  if (!must_read || next == 0)
    SVN_ERR(read_item(&stream, fs, rev_file, entry, scratch_pool));

  /* Seek to the block to read within the changes list. */
  SVN_ERR(svn_fs_x__rev_file_seek(rev_file, NULL,
                                  entry->offset + next_offset));
  SVN_ERR(svn_fs_x__rev_file_stream(&stream, rev_file));

  /* read changes from revision file */
  SVN_ERR(svn_fs_x__read_changes(changes, stream, SVN_FS_X__CHANGES_BLOCK_SIZE,
                                 result_pool, scratch_pool));

  SVN_ERR(svn_fs_x__rev_file_offset(&changes_list.end_offset, rev_file));
  changes_list.end_offset -= entry->offset;
  changes_list.start_offset = next_offset;
  changes_list.count = (*changes)->nelts;
  changes_list.changes = (svn_fs_x__change_t **)(*changes)->elts;
  changes_list.eol =    (changes_list.count < SVN_FS_X__CHANGES_BLOCK_SIZE)
                     || (changes_list.end_offset + 1 >= entry->size);

  /* cache for future reference */

  SVN_ERR(svn_cache__set(ffd->changes_cache, &key, &changes_list,
                         scratch_pool));

  /* Trim the result:
   * Remove the entries that already been reported. */
  if (must_read)
    {
      context->next_offset = changes_list.end_offset;
      context->eol = changes_list.eol;
    }

  return SVN_NO_ERROR;
}