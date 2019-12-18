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
typedef  int /*<<< orphan*/  svn_fs_fs__dir_data_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * return_serialized_dir_context (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serialize_dir (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__serialize_dir_entries(void **data,
                                 apr_size_t *data_len,
                                 void *in,
                                 apr_pool_t *pool)
{
  svn_fs_fs__dir_data_t *dir = in;

  /* serialize the dir content into a new serialization context
   * and return the serialized data */
  return return_serialized_dir_context(serialize_dir(dir, pool),
                                       data,
                                       data_len,
                                       FALSE);
}