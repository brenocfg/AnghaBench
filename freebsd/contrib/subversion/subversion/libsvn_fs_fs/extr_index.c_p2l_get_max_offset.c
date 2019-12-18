#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_12__ {TYPE_5__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
struct TYPE_13__ {int /*<<< orphan*/  is_packed; int /*<<< orphan*/  start_revision; } ;
typedef  TYPE_2__ svn_fs_fs__revision_file_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_14__ {int /*<<< orphan*/  second; int /*<<< orphan*/  revision; } ;
typedef  TYPE_3__ pair_cache_key_t ;
struct TYPE_15__ {int /*<<< orphan*/  file_size; } ;
typedef  TYPE_4__ p2l_header_t ;
struct TYPE_16__ {int /*<<< orphan*/  p2l_header_cache; } ;
typedef  TYPE_5__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_p2l_header (TYPE_4__**,TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p2l_get_max_offset_func ; 
 int /*<<< orphan*/  svn_cache__get_partial (void**,scalar_t__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
p2l_get_max_offset(apr_off_t *offset,
                   svn_fs_t *fs,
                   svn_fs_fs__revision_file_t *rev_file,
                   svn_revnum_t revision,
                   apr_pool_t *scratch_pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;
  p2l_header_t *header;
  svn_boolean_t is_cached = FALSE;
  apr_off_t *offset_p;

  /* look for the header data in our cache */
  pair_cache_key_t key;
  key.revision = rev_file->start_revision;
  key.second = rev_file->is_packed;

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