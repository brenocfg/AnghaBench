#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_x__revision_file_t ;
struct TYPE_11__ {int /*<<< orphan*/  second; int /*<<< orphan*/  revision; } ;
typedef  TYPE_1__ svn_fs_x__pair_cache_key_t ;
struct TYPE_12__ {int /*<<< orphan*/  p2l_header_cache; } ;
typedef  TYPE_2__ svn_fs_x__data_t ;
struct TYPE_13__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_3__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_14__ {int /*<<< orphan*/  file_size; } ;
typedef  TYPE_4__ p2l_header_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  base_revision (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_p2l_header (TYPE_4__**,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2l_get_max_offset_func ; 
 int /*<<< orphan*/  svn_cache__get_partial (void**,scalar_t__*,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__is_packed_rev (TYPE_3__*,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_fs_x__p2l_get_max_offset(apr_off_t *offset,
                             svn_fs_t *fs,
                             svn_fs_x__revision_file_t *rev_file,
                             svn_revnum_t revision,
                             apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  p2l_header_t *header;
  svn_boolean_t is_cached = FALSE;
  apr_off_t *offset_p;

  /* look for the header data in our cache */
  svn_fs_x__pair_cache_key_t key;
  key.revision = base_revision(fs, revision);
  key.second = svn_fs_x__is_packed_rev(fs, revision);

  SVN_ERR(svn_cache__get_partial((void **)&offset_p, &is_cached,
                                 ffd->p2l_header_cache, &key,
                                 p2l_get_max_offset_func, NULL,
                                 scratch_pool));
  if (is_cached)
    {
      *offset = *offset_p;
      return SVN_NO_ERROR;
    }

  SVN_ERR(get_p2l_header(&header, rev_file, fs, revision, scratch_pool,
                         scratch_pool));
  *offset = header->file_size;

  return SVN_NO_ERROR;
}