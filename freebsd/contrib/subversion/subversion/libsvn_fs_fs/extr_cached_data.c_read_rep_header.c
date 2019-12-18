#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
struct TYPE_4__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__rep_header_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  pair_cache_key_t ;
struct TYPE_5__ {scalar_t__ rep_header_cache; } ;
typedef  TYPE_2__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_cache__get (void**,scalar_t__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_cache__set (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__read_rep_header (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
read_rep_header(svn_fs_fs__rep_header_t **rep_header,
                svn_fs_t *fs,
                svn_stream_t *stream,
                pair_cache_key_t *key,
                apr_pool_t *result_pool,
                apr_pool_t *scratch_pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;
  svn_boolean_t is_cached = FALSE;

  if (ffd->rep_header_cache)
    {
      SVN_ERR(svn_cache__get((void**)rep_header, &is_cached,
                             ffd->rep_header_cache, key,
                             result_pool));
      if (is_cached)
        return SVN_NO_ERROR;
    }

  SVN_ERR(svn_fs_fs__read_rep_header(rep_header, stream, result_pool,
                                     scratch_pool));

  if (ffd->rep_header_cache)
    SVN_ERR(svn_cache__set(ffd->rep_header_cache, key, *rep_header,
                           scratch_pool));

  return SVN_NO_ERROR;
}