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
typedef  int /*<<< orphan*/  dir_data_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 void* deserialize_dir (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_x__deserialize_dir_entries(void **out,
                                  void *data,
                                  apr_size_t data_len,
                                  apr_pool_t *result_pool)
{
  /* Copy the _full_ buffer as it also contains the sub-structures. */
  dir_data_t *dir_data = (dir_data_t *)data;

  /* reconstruct the hash from the serialized data */
  *out = deserialize_dir(dir_data, dir_data, result_pool);

  return SVN_NO_ERROR;
}