#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_15__ {TYPE_6__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
struct TYPE_16__ {scalar_t__ start_revision; int p2l_offset; int l2p_offset; int /*<<< orphan*/  l2p_stream; int /*<<< orphan*/  is_packed; } ;
typedef  TYPE_3__ svn_fs_fs__revision_file_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_17__ {scalar_t__ revision; int /*<<< orphan*/  second; } ;
typedef  TYPE_4__ pair_cache_key_t ;
struct TYPE_18__ {scalar_t__ first_revision; int page_size; int revision_count; int* page_table_index; TYPE_1__* page_table; } ;
typedef  TYPE_5__ l2p_header_t ;
struct TYPE_19__ {int /*<<< orphan*/  l2p_header_cache; scalar_t__ max_files_per_dir; } ;
typedef  TYPE_6__ fs_fs_data_t ;
typedef  int apr_uint64_t ;
typedef  void* apr_uint32_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;
struct TYPE_14__ {void* size; int /*<<< orphan*/  offset; void* entry_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_INDEX_CORRUPTION ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  auto_open_l2p_index (TYPE_3__*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  packed_stream_get (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packed_stream_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  packed_stream_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_cache__set (int /*<<< orphan*/ ,TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static svn_error_t *
get_l2p_header_body(l2p_header_t **header,
                    svn_fs_fs__revision_file_t *rev_file,
                    svn_fs_t *fs,
                    svn_revnum_t revision,
                    apr_pool_t *result_pool,
                    apr_pool_t *scratch_pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;
  apr_uint64_t value;
  apr_size_t i;
  apr_size_t page, page_count;
  apr_off_t offset;
  l2p_header_t *result = apr_pcalloc(result_pool, sizeof(*result));
  apr_size_t page_table_index;
  svn_revnum_t next_rev;

  pair_cache_key_t key;
  key.revision = rev_file->start_revision;
  key.second = rev_file->is_packed;

  SVN_ERR(auto_open_l2p_index(rev_file, fs, revision));
  packed_stream_seek(rev_file->l2p_stream, 0);

  /* Read the table sizes.  Check the data for plausibility and
   * consistency with other bits. */
  SVN_ERR(packed_stream_get(&value, rev_file->l2p_stream));
  result->first_revision = (svn_revnum_t)value;
  if (result->first_revision != rev_file->start_revision)
    return svn_error_create(SVN_ERR_FS_INDEX_CORRUPTION, NULL,
                  _("Index rev / pack file revision numbers do not match"));

  SVN_ERR(packed_stream_get(&value, rev_file->l2p_stream));
  result->page_size = (apr_uint32_t)value;
  if (!result->page_size || (result->page_size & (result->page_size - 1)))
    return svn_error_create(SVN_ERR_FS_INDEX_CORRUPTION, NULL,
                            _("L2P index page size is not a power of two"));

  SVN_ERR(packed_stream_get(&value, rev_file->l2p_stream));
  result->revision_count = (int)value;
  if (   result->revision_count != 1
      && result->revision_count != (apr_uint64_t)ffd->max_files_per_dir)
    return svn_error_create(SVN_ERR_FS_INDEX_CORRUPTION, NULL,
                            _("Invalid number of revisions in L2P index"));

  SVN_ERR(packed_stream_get(&value, rev_file->l2p_stream));
  page_count = (apr_size_t)value;
  if (page_count < result->revision_count)
    return svn_error_create(SVN_ERR_FS_INDEX_CORRUPTION, NULL,
                            _("Fewer L2P index pages than revisions"));
  if (page_count > (rev_file->p2l_offset - rev_file->l2p_offset) / 2)
    return svn_error_create(SVN_ERR_FS_INDEX_CORRUPTION, NULL,
                            _("L2P index page count implausibly large"));

  next_rev = result->first_revision + (svn_revnum_t)result->revision_count;
  if (result->first_revision > revision || next_rev <= revision)
    return svn_error_createf(SVN_ERR_FS_INDEX_CORRUPTION, NULL,
                      _("Corrupt L2P index for r%ld only covers r%ld:%ld"),
                      revision, result->first_revision, next_rev);

  /* allocate the page tables */
  result->page_table
    = apr_pcalloc(result_pool, page_count * sizeof(*result->page_table));
  result->page_table_index
    = apr_pcalloc(result_pool, (result->revision_count + 1)
                             * sizeof(*result->page_table_index));

  /* read per-revision page table sizes (i.e. number of pages per rev) */
  page_table_index = 0;
  result->page_table_index[0] = page_table_index;

  for (i = 0; i < result->revision_count; ++i)
    {
      SVN_ERR(packed_stream_get(&value, rev_file->l2p_stream));
      if (value == 0)
        return svn_error_create(SVN_ERR_FS_INDEX_CORRUPTION, NULL,
                                _("Revision with no L2P index pages"));

      page_table_index += (apr_size_t)value;
      if (page_table_index > page_count)
        return svn_error_create(SVN_ERR_FS_INDEX_CORRUPTION, NULL,
                                _("L2P page table exceeded"));

      result->page_table_index[i+1] = page_table_index;
    }

  if (page_table_index != page_count)
    return svn_error_create(SVN_ERR_FS_INDEX_CORRUPTION, NULL,
                 _("Revisions do not cover the full L2P index page table"));

  /* read actual page tables */
  for (page = 0; page < page_count; ++page)
    {
      SVN_ERR(packed_stream_get(&value, rev_file->l2p_stream));
      if (value == 0)
        return svn_error_create(SVN_ERR_FS_INDEX_CORRUPTION, NULL,
                                _("Empty L2P index page"));

      result->page_table[page].size = (apr_uint32_t)value;
      SVN_ERR(packed_stream_get(&value, rev_file->l2p_stream));
      if (value > result->page_size)
        return svn_error_create(SVN_ERR_FS_INDEX_CORRUPTION, NULL,
                                _("Page exceeds L2P index page size"));

      result->page_table[page].entry_count = (apr_uint32_t)value;
    }

  /* correct the page description offsets */
  offset = packed_stream_offset(rev_file->l2p_stream);
  for (page = 0; page < page_count; ++page)
    {
      result->page_table[page].offset = offset;
      offset += result->page_table[page].size;
    }

  /* return and cache the header */
  *header = result;
  SVN_ERR(svn_cache__set(ffd->l2p_header_cache, &key, result, scratch_pool));

  return SVN_NO_ERROR;
}