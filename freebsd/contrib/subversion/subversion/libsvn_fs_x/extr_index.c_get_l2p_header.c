#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_fs_x__revision_file_t ;
struct TYPE_9__ {int /*<<< orphan*/  is_packed; int /*<<< orphan*/  start_revision; } ;
typedef  TYPE_1__ svn_fs_x__rev_file_info_t ;
struct TYPE_10__ {int /*<<< orphan*/  second; int /*<<< orphan*/  revision; } ;
typedef  TYPE_2__ svn_fs_x__pair_cache_key_t ;
struct TYPE_11__ {int /*<<< orphan*/  l2p_header_cache; } ;
typedef  TYPE_3__ svn_fs_x__data_t ;
struct TYPE_12__ {TYPE_3__* fsap_data; } ;
typedef  TYPE_4__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  l2p_header_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  get_l2p_header_body (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__get (void**,scalar_t__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__rev_file_info (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
get_l2p_header(l2p_header_t **header,
               svn_fs_x__revision_file_t *rev_file,
               svn_fs_t *fs,
               svn_revnum_t revision,
               apr_pool_t *result_pool,
               apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  svn_boolean_t is_cached = FALSE;
  svn_fs_x__rev_file_info_t file_info;

  /* first, try cache lookop */
  svn_fs_x__pair_cache_key_t key;
  SVN_ERR(svn_fs_x__rev_file_info(&file_info, rev_file));
  key.revision = file_info.start_revision;
  key.second = file_info.is_packed;
  SVN_ERR(svn_cache__get((void**)header, &is_cached, ffd->l2p_header_cache,
                         &key, result_pool));
  if (is_cached)
    return SVN_NO_ERROR;

  /* read from disk and cache the result */
  SVN_ERR(get_l2p_header_body(header, rev_file, fs, revision, result_pool,
                              scratch_pool));

  return SVN_NO_ERROR;
}