#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_8__ {int /*<<< orphan*/  l2p_stream; } ;
typedef  TYPE_1__ svn_fs_fs__revision_file_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_9__ {scalar_t__ offset; int entry_count; scalar_t__ size; } ;
typedef  TYPE_2__ l2p_page_table_entry_t ;
struct TYPE_10__ {int entry_count; scalar_t__* offsets; } ;
typedef  TYPE_3__ l2p_page_t ;
typedef  scalar_t__ apr_uint64_t ;
typedef  size_t apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_INDEX_CORRUPTION ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  auto_open_l2p_index (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ decode_int (scalar_t__) ; 
 int /*<<< orphan*/  packed_stream_get (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ packed_stream_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packed_stream_seek (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
get_l2p_page(l2p_page_t **page,
             svn_fs_fs__revision_file_t *rev_file,
             svn_fs_t *fs,
             svn_revnum_t start_revision,
             l2p_page_table_entry_t *table_entry,
             apr_pool_t *result_pool)
{
  apr_uint32_t i;
  l2p_page_t *result = apr_pcalloc(result_pool, sizeof(*result));
  apr_uint64_t last_value = 0;

  /* open index file and select page */
  SVN_ERR(auto_open_l2p_index(rev_file, fs, start_revision));
  packed_stream_seek(rev_file->l2p_stream, table_entry->offset);

  /* initialize the page content */
  result->entry_count = table_entry->entry_count;
  result->offsets = apr_pcalloc(result_pool, result->entry_count
                                           * sizeof(*result->offsets));

  /* read all page entries (offsets in rev file and container sub-items) */
  for (i = 0; i < result->entry_count; ++i)
    {
      apr_uint64_t value = 0;
      SVN_ERR(packed_stream_get(&value, rev_file->l2p_stream));
      last_value += decode_int(value);
      result->offsets[i] = last_value - 1;
    }

  /* After reading all page entries, the read cursor must have moved by
   * TABLE_ENTRY->SIZE bytes. */
  if (   packed_stream_offset(rev_file->l2p_stream)
      != table_entry->offset + table_entry->size)
    return svn_error_create(SVN_ERR_FS_INDEX_CORRUPTION, NULL,
                _("L2P actual page size does not match page table value."));

  *page = result;

  return SVN_NO_ERROR;
}