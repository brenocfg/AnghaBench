#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_x__revision_file_t ;
struct TYPE_13__ {int /*<<< orphan*/  page; int /*<<< orphan*/  is_packed; scalar_t__ revision; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ svn_fs_x__page_cache_key_t ;
struct TYPE_14__ {int /*<<< orphan*/  p2l_page_cache; } ;
typedef  TYPE_2__ svn_fs_x__data_t ;
struct TYPE_15__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_3__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_16__ {int /*<<< orphan*/  page_size; int /*<<< orphan*/  page_start; int /*<<< orphan*/  next_offset; int /*<<< orphan*/  start_offset; scalar_t__ first_revision; int /*<<< orphan*/  page_no; scalar_t__ revision; } ;
typedef  TYPE_4__ p2l_page_info_baton_t ;
typedef  scalar_t__ apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 scalar_t__ APR_UINT32_MAX ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_p2l_page (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_3__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_p2l_page_info (TYPE_4__*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__has_key (scalar_t__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__set (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__is_packed_rev (TYPE_3__*,scalar_t__) ; 

__attribute__((used)) static svn_error_t *
prefetch_p2l_page(svn_boolean_t *end,
                  int *leaking_bucket,
                  svn_fs_t *fs,
                  svn_fs_x__revision_file_t *rev_file,
                  p2l_page_info_baton_t *baton,
                  apr_off_t min_offset,
                  apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  svn_boolean_t already_cached;
  apr_array_header_t *page;
  svn_fs_x__page_cache_key_t key = { 0 };

  /* fetch the page info */
  *end = FALSE;
  baton->revision = baton->first_revision;
  SVN_ERR(get_p2l_page_info(baton, rev_file, fs, scratch_pool));
  if (baton->start_offset < min_offset)
    {
      /* page outside limits -> stop prefetching */
      *end = TRUE;
      return SVN_NO_ERROR;
    }

  /* do we have that page in our caches already? */
  assert(baton->first_revision <= APR_UINT32_MAX);
  key.revision = (apr_uint32_t)baton->first_revision;
  key.is_packed = svn_fs_x__is_packed_rev(fs, baton->first_revision);
  key.page = baton->page_no;
  SVN_ERR(svn_cache__has_key(&already_cached, ffd->p2l_page_cache,
                             &key, scratch_pool));

  /* yes, already cached */
  if (already_cached)
    {
      /* stop prefetching if most pages are already cached. */
      if (!--*leaking_bucket)
        *end = TRUE;

      return SVN_NO_ERROR;
    }

  ++*leaking_bucket;

  /* read from disk */
  SVN_ERR(get_p2l_page(&page, rev_file, fs,
                       baton->first_revision,
                       baton->start_offset,
                       baton->next_offset,
                       baton->page_start,
                       baton->page_size,
                       scratch_pool));

  /* and put it into our cache */
  SVN_ERR(svn_cache__set(ffd->p2l_page_cache, &key, page, scratch_pool));

  return SVN_NO_ERROR;
}