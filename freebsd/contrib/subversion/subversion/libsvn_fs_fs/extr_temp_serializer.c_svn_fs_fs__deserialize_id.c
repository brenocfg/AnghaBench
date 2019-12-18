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
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_fs__id_deserialize (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

svn_error_t *
svn_fs_fs__deserialize_id(void **out,
                          void *data,
                          apr_size_t data_len,
                          apr_pool_t *pool)
{
  /* Copy the _full_ buffer as it also contains the sub-structures. */
  svn_fs_id_t *id = (svn_fs_id_t *)data;

  /* fixup of all pointers etc. */
  svn_fs_fs__id_deserialize(id, &id);

  /* done */
  *out = id;
  return SVN_NO_ERROR;
}