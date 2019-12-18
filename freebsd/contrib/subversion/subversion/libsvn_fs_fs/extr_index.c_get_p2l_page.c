#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_4__ {int /*<<< orphan*/  p2l_stream; } ;
typedef  TYPE_1__ svn_fs_fs__revision_file_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__p2l_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_off_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_INDEX_CORRUPTION ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  auto_open_p2l_index (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packed_stream_get (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ packed_stream_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packed_stream_seek (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  read_entry (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
get_p2l_page(apr_array_header_t **entries,
             svn_fs_fs__revision_file_t *rev_file,
             svn_fs_t *fs,
             svn_revnum_t start_revision,
             apr_off_t start_offset,
             apr_off_t next_offset,
             apr_off_t page_start,
             apr_uint64_t page_size,
             apr_pool_t *result_pool)
{
  apr_uint64_t value;
  apr_array_header_t *result
    = apr_array_make(result_pool, 16, sizeof(svn_fs_fs__p2l_entry_t));
  apr_off_t item_offset;
  apr_off_t offset;
  svn_revnum_t last_revision;
  apr_uint64_t last_compound;

  /* open index and navigate to page start */
  SVN_ERR(auto_open_p2l_index(rev_file, fs, start_revision));
  packed_stream_seek(rev_file->p2l_stream, start_offset);

  /* read rev file offset of the first page entry (all page entries will
   * only store their sizes). */
  SVN_ERR(packed_stream_get(&value, rev_file->p2l_stream));
  item_offset = (apr_off_t)value;

  /* read all entries of this page */
  last_revision = start_revision;
  last_compound = 0;

  /* Special case: empty pages. */
  if (start_offset == next_offset)
    {
      /* Empty page. This only happens if the first entry of the next page
       * also covers this page (and possibly more) completely. */
      SVN_ERR(read_entry(rev_file->p2l_stream, &item_offset,
                         &last_revision, &last_compound, result));
    }
  else
    {
      /* Read non-empty page. */
      do
        {
          SVN_ERR(read_entry(rev_file->p2l_stream, &item_offset,
                             &last_revision, &last_compound, result));
          offset = packed_stream_offset(rev_file->p2l_stream);
        }
      while (offset < next_offset);

      /* We should now be exactly at the next offset, i.e. the numbers in
       * the stream cannot overlap into the next page description. */
      if (offset != next_offset)
        return svn_error_create(SVN_ERR_FS_INDEX_CORRUPTION, NULL,
             _("P2L page description overlaps with next page description"));

      /* if we haven't covered the cluster end yet, we must read the first
       * entry of the next page */
      if (item_offset < page_start + page_size)
        {
          SVN_ERR(packed_stream_get(&value, rev_file->p2l_stream));
          item_offset = (apr_off_t)value;
          last_revision = start_revision;
          last_compound = 0;
          SVN_ERR(read_entry(rev_file->p2l_stream, &item_offset,
                             &last_revision, &last_compound, result));
        }
    }

  *entries = result;

  return SVN_NO_ERROR;
}