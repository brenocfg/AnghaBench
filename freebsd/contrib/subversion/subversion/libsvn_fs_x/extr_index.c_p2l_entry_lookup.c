#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_x__revision_file_t ;
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ svn_fs_x__page_cache_key_t ;
typedef  int /*<<< orphan*/  svn_fs_x__p2l_entry_t ;
struct TYPE_10__ {int /*<<< orphan*/  p2l_page_cache; } ;
typedef  TYPE_2__ svn_fs_x__data_t ;
struct TYPE_11__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_3__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  p2l_page_info_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_off_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ compare_p2l_entry_offsets ; 
 int /*<<< orphan*/  get_p2l_keys (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2l_entry_lookup_func ; 
 int /*<<< orphan*/  p2l_index_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__get_partial (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_sort__array_lookup (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int (*) (void const*,void const*)) ; 

__attribute__((used)) static svn_error_t *
p2l_entry_lookup(svn_fs_x__p2l_entry_t **entry_p,
                 svn_fs_x__revision_file_t *rev_file,
                 svn_fs_t *fs,
                 svn_revnum_t revision,
                 apr_off_t offset,
                 apr_pool_t *result_pool,
                 apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  svn_fs_x__page_cache_key_t key = { 0 };
  svn_boolean_t is_cached = FALSE;
  p2l_page_info_baton_t page_info;

  /* look for this info in our cache */
  SVN_ERR(get_p2l_keys(&page_info, &key, rev_file, fs, revision, offset,
                       scratch_pool));
  SVN_ERR(svn_cache__get_partial((void**)entry_p, &is_cached,
                                 ffd->p2l_page_cache, &key,
                                 p2l_entry_lookup_func, &offset,
                                 result_pool));
  if (!is_cached)
    {
      /* do a standard index lookup.  This is will automatically prefetch
       * data to speed up future lookups. */
      apr_array_header_t *entries = apr_array_make(result_pool, 1,
                                                   sizeof(**entry_p));
      SVN_ERR(p2l_index_lookup(entries, rev_file, fs, revision, offset,
                               offset + 1, scratch_pool));

      /* Find the entry that we want. */
      *entry_p = svn_sort__array_lookup(entries, &offset, NULL,
          (int (*)(const void *, const void *))compare_p2l_entry_offsets);
    }

  return SVN_NO_ERROR;
}