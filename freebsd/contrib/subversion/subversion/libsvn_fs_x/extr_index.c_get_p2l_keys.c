#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_x__revision_file_t ;
struct TYPE_6__ {scalar_t__ page; int /*<<< orphan*/  is_packed; scalar_t__ revision; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ svn_fs_x__page_cache_key_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {scalar_t__ page_count; scalar_t__ page_no; scalar_t__ first_revision; int /*<<< orphan*/  revision; int /*<<< orphan*/  offset; } ;
typedef  TYPE_2__ p2l_page_info_baton_t ;
typedef  scalar_t__ apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;

/* Variables and functions */
 scalar_t__ APR_UINT32_MAX ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_INDEX_OVERFLOW ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_off_t_toa (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_p2l_page_info (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__is_packed_rev (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
get_p2l_keys(p2l_page_info_baton_t *page_info_p,
             svn_fs_x__page_cache_key_t *key_p,
             svn_fs_x__revision_file_t *rev_file,
             svn_fs_t *fs,
             svn_revnum_t revision,
             apr_off_t offset,
             apr_pool_t *scratch_pool)
{
  p2l_page_info_baton_t page_info;

  /* request info for the index pages that describes the pack / rev file
   * contents at pack / rev file position OFFSET. */
  page_info.offset = offset;
  page_info.revision = revision;
  SVN_ERR(get_p2l_page_info(&page_info, rev_file, fs, scratch_pool));

  /* if the offset refers to a non-existent page, bail out */
  if (page_info.page_count <= page_info.page_no)
    return svn_error_createf(SVN_ERR_FS_INDEX_OVERFLOW , NULL,
                             _("Offset %s too large in revision %ld"),
                             apr_off_t_toa(scratch_pool, offset), revision);

  /* return results */
  if (page_info_p)
    *page_info_p = page_info;

  /* construct cache key */
  if (key_p)
    {
      svn_fs_x__page_cache_key_t key = { 0 };
      assert(page_info.first_revision <= APR_UINT32_MAX);
      key.revision = (apr_uint32_t)page_info.first_revision;
      key.is_packed = svn_fs_x__is_packed_rev(fs, revision);
      key.page = page_info.page_no;

      *key_p = key;
    }

  return SVN_NO_ERROR;
}