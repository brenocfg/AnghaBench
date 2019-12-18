#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_20__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_x__revision_file_t ;
struct TYPE_21__ {int page; int /*<<< orphan*/  is_packed; scalar_t__ revision; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ svn_fs_x__page_cache_key_t ;
struct TYPE_23__ {int /*<<< orphan*/  l2p_page_cache; scalar_t__ block_size; } ;
typedef  TYPE_2__ svn_fs_x__data_t ;
struct TYPE_24__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_3__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  l2p_page_table_entry_t ;
struct TYPE_25__ {int /*<<< orphan*/  sub_items; int /*<<< orphan*/  offsets; } ;
typedef  TYPE_4__ l2p_page_t ;
struct TYPE_22__ {scalar_t__ size; scalar_t__ offset; } ;
struct TYPE_26__ {int page_no; scalar_t__ first_revision; TYPE_20__ entry; int /*<<< orphan*/  page_offset; void* item_index; scalar_t__ revision; } ;
typedef  TYPE_5__ l2p_page_info_baton_t ;
struct TYPE_27__ {scalar_t__ sub_item; scalar_t__ offset; int /*<<< orphan*/  page_offset; void* item_index; scalar_t__ revision; } ;
typedef  TYPE_6__ l2p_page_baton_t ;
typedef  void* apr_uint64_t ;
typedef  scalar_t__ apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_off_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 scalar_t__ APR_ALIGN (scalar_t__,scalar_t__) ; 
 scalar_t__ APR_UINT32_MAX ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_l2p_page (TYPE_4__**,int /*<<< orphan*/ *,TYPE_20__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_l2p_page_info (TYPE_5__*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2p_page_access_func ; 
 int /*<<< orphan*/  l2p_page_get_offset (TYPE_6__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prefetch_l2p_pages (scalar_t__*,TYPE_3__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__get_partial (void**,scalar_t__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__set (int /*<<< orphan*/ ,TYPE_1__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__is_packed_rev (TYPE_3__*,scalar_t__) ; 
 scalar_t__ svn_fs_x__pack_size (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
l2p_index_lookup(apr_off_t *offset,
                 apr_uint32_t *sub_item,
                 svn_fs_t *fs,
                 svn_fs_x__revision_file_t *rev_file,
                 svn_revnum_t revision,
                 apr_uint64_t item_index,
                 apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  l2p_page_info_baton_t info_baton;
  l2p_page_baton_t page_baton;
  l2p_page_t *page = NULL;
  svn_fs_x__page_cache_key_t key = { 0 };
  svn_boolean_t is_cached = FALSE;
  void *dummy = NULL;

  /* read index master data structure and extract the info required to
   * access the l2p index page for (REVISION,ITEM_INDEX)*/
  info_baton.revision = revision;
  info_baton.item_index = item_index;
  SVN_ERR(get_l2p_page_info(&info_baton, rev_file, fs, scratch_pool));

  /* try to find the page in the cache and get the OFFSET from it */
  page_baton.revision = revision;
  page_baton.item_index = item_index;
  page_baton.page_offset = info_baton.page_offset;

  assert(revision <= APR_UINT32_MAX);
  key.revision = (apr_uint32_t)revision;
  key.is_packed = svn_fs_x__is_packed_rev(fs, revision);
  key.page = info_baton.page_no;

  SVN_ERR(svn_cache__get_partial(&dummy, &is_cached,
                                 ffd->l2p_page_cache, &key,
                                 l2p_page_access_func, &page_baton,
                                 scratch_pool));

  if (!is_cached)
    {
      /* we need to read the info from disk (might already be in the
       * APR file buffer, though) */
      apr_array_header_t *pages;
      svn_revnum_t prefetch_revision;
      svn_revnum_t last_revision
        = info_baton.first_revision
          + svn_fs_x__pack_size(fs, info_baton.first_revision);
      apr_pool_t *iterpool = svn_pool_create(scratch_pool);
      svn_boolean_t end;
      apr_off_t max_offset
        = APR_ALIGN(info_baton.entry.offset + info_baton.entry.size,
                    ffd->block_size);
      apr_off_t min_offset = max_offset - ffd->block_size;

      /* read the relevant page */
      SVN_ERR(get_l2p_page(&page, rev_file, &info_baton.entry, scratch_pool));

      /* cache the page and extract the result we need */
      SVN_ERR(svn_cache__set(ffd->l2p_page_cache, &key, page, scratch_pool));
      SVN_ERR(l2p_page_get_offset(&page_baton, page, page->offsets,
                                  page->sub_items, scratch_pool));

      /* prefetch pages from following and preceding revisions */
      pages = apr_array_make(scratch_pool, 16,
                             sizeof(l2p_page_table_entry_t));
      end = FALSE;
      for (prefetch_revision = revision;
           prefetch_revision < last_revision && !end;
           ++prefetch_revision)
        {
          int excluded_page_no = prefetch_revision == revision
                               ? info_baton.page_no
                               : -1;
          svn_pool_clear(iterpool);

          SVN_ERR(prefetch_l2p_pages(&end, fs, rev_file,
                                     prefetch_revision, pages,
                                     excluded_page_no, min_offset,
                                     max_offset, iterpool));
        }

      end = FALSE;
      for (prefetch_revision = revision-1;
           prefetch_revision >= info_baton.first_revision && !end;
           --prefetch_revision)
        {
          svn_pool_clear(iterpool);

          SVN_ERR(prefetch_l2p_pages(&end, fs, rev_file,
                                     prefetch_revision, pages, -1,
                                     min_offset, max_offset, iterpool));
        }

      svn_pool_destroy(iterpool);
    }

  *offset = page_baton.offset;
  *sub_item = page_baton.sub_item;

  return SVN_NO_ERROR;
}