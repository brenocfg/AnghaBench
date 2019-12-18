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
typedef  int /*<<< orphan*/  svn_fs_x__revision_file_t ;
typedef  int /*<<< orphan*/  svn_fs_x__packed_number_stream_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_5__ {scalar_t__ offset; int entry_count; scalar_t__ size; } ;
typedef  TYPE_1__ l2p_page_table_entry_t ;
struct TYPE_6__ {int entry_count; int* offsets; int* sub_items; } ;
typedef  TYPE_2__ l2p_page_t ;
typedef  int apr_uint64_t ;
typedef  int apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  void* apr_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_INDEX_CORRUPTION ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  packed_stream_get (int*,int /*<<< orphan*/ *) ; 
 scalar_t__ packed_stream_offset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packed_stream_seek (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_l2p_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_l2p_page(l2p_page_t **page,
             svn_fs_x__revision_file_t *rev_file,
             l2p_page_table_entry_t *table_entry,
             apr_pool_t *result_pool)
{
  apr_uint64_t value, last_value = 0;
  apr_uint32_t i;
  l2p_page_t *result = apr_pcalloc(result_pool, sizeof(*result));
  apr_uint64_t container_count;
  apr_off_t *container_offsets;
  svn_fs_x__packed_number_stream_t *stream;

  /* open index file and select page */
  SVN_ERR(svn_fs_x__rev_file_l2p_index(&stream, rev_file));
  packed_stream_seek(stream, table_entry->offset);

  /* initialize the page content */
  result->entry_count = table_entry->entry_count;
  result->offsets = apr_pcalloc(result_pool, result->entry_count
                                           * sizeof(*result->offsets));
  result->sub_items = apr_pcalloc(result_pool, result->entry_count
                                             * sizeof(*result->sub_items));

  /* container offsets array */

  SVN_ERR(packed_stream_get(&container_count, stream));
  container_offsets = apr_pcalloc(result_pool,
                                  container_count * sizeof(*result));
  for (i = 0; i < container_count; ++i)
    {
      SVN_ERR(packed_stream_get(&value, stream));
      last_value += value;
      container_offsets[i] = (apr_off_t)last_value - 1;
      /* '-1' is represented as '0' in the index file */
    }

  /* read all page entries (offsets in rev file and container sub-items) */
  for (i = 0; i < result->entry_count; ++i)
    {
      SVN_ERR(packed_stream_get(&value, stream));
      if (value == 0)
        {
          result->offsets[i] = -1;
          result->sub_items[i] = 0;
        }
      else if (value <= container_count)
        {
          result->offsets[i] = container_offsets[value - 1];
          SVN_ERR(packed_stream_get(&value, stream));
          result->sub_items[i] = (apr_uint32_t)value;
        }
      else
        {
          result->offsets[i] = (apr_off_t)(value - 1 - container_count);
          result->sub_items[i] = 0;
        }
    }

  /* After reading all page entries, the read cursor must have moved by
   * TABLE_ENTRY->SIZE bytes. */
  if (   packed_stream_offset(stream)
      != table_entry->offset + table_entry->size)
    return svn_error_create(SVN_ERR_FS_INDEX_CORRUPTION, NULL,
                _("L2P actual page size does not match page table value."));

  *page = result;

  return SVN_NO_ERROR;
}