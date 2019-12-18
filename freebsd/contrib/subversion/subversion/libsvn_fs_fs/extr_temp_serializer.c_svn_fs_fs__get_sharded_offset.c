#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_off_t ;
typedef  size_t apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 

svn_error_t *
svn_fs_fs__get_sharded_offset(void **out,
                              const void *data,
                              apr_size_t data_len,
                              void *baton,
                              apr_pool_t *pool)
{
  const apr_off_t *manifest = data;
  apr_int64_t shard_pos = *(apr_int64_t *)baton;

  *(apr_off_t *)out = manifest[shard_pos];

  return SVN_NO_ERROR;
}