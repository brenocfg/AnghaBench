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
typedef  int /*<<< orphan*/  svn_fs_fs__rep_header_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_palloc (int /*<<< orphan*/ *,int) ; 

svn_error_t *
svn_fs_fs__deserialize_rep_header(void **out,
                                  void *data,
                                  apr_size_t data_len,
                                  apr_pool_t *pool)
{
  svn_fs_fs__rep_header_t *copy = apr_palloc(pool, sizeof(*copy));
  SVN_ERR_ASSERT(data_len == sizeof(*copy));

  *copy = *(svn_fs_fs__rep_header_t *)data;
  *out = data;

  return SVN_NO_ERROR;
}