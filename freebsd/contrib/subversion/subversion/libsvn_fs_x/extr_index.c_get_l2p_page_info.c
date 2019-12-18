#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_x__revision_file_t ;
struct TYPE_16__ {int /*<<< orphan*/  second; int /*<<< orphan*/  revision; } ;
typedef  TYPE_1__ svn_fs_x__pair_cache_key_t ;
struct TYPE_17__ {int /*<<< orphan*/  l2p_header_cache; } ;
typedef  TYPE_2__ svn_fs_x__data_t ;
struct TYPE_18__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_3__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_19__ {int /*<<< orphan*/  revision; } ;
typedef  TYPE_4__ l2p_page_info_baton_t ;
struct TYPE_20__ {int /*<<< orphan*/  page_table_index; int /*<<< orphan*/  page_table; } ;
typedef  TYPE_5__ l2p_header_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  base_revision (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_l2p_header_body (TYPE_5__**,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2p_header_access_func ; 
 int /*<<< orphan*/  l2p_header_copy (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__get_partial (void**,scalar_t__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__is_packed_rev (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
get_l2p_page_info(l2p_page_info_baton_t *baton,
                  svn_fs_x__revision_file_t *rev_file,
                  svn_fs_t *fs,
                  apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  l2p_header_t *result;
  svn_boolean_t is_cached = FALSE;
  void *dummy = NULL;

  /* try to find the info in the cache */
  svn_fs_x__pair_cache_key_t key;
  key.revision = base_revision(fs, baton->revision);
  key.second = svn_fs_x__is_packed_rev(fs, baton->revision);
  SVN_ERR(svn_cache__get_partial((void**)&dummy, &is_cached,
                                 ffd->l2p_header_cache, &key,
                                 l2p_header_access_func, baton,
                                 scratch_pool));
  if (is_cached)
    return SVN_NO_ERROR;

  /* read from disk, cache and copy the result */
  SVN_ERR(get_l2p_header_body(&result, rev_file, fs, baton->revision,
                              scratch_pool, scratch_pool));
  SVN_ERR(l2p_header_copy(baton, result, result->page_table,
                          result->page_table_index, scratch_pool));

  return SVN_NO_ERROR;
}