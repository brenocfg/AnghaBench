#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int count; int /*<<< orphan*/ * changes; } ;
typedef  TYPE_1__ svn_fs_fs__changes_list_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  change_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  deserialize_change (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  svn_temp_deserializer__resolve (TYPE_1__*,void**) ; 

svn_error_t *
svn_fs_fs__deserialize_changes(void **out,
                               void *data,
                               apr_size_t data_len,
                               apr_pool_t *pool)
{
  int i;
  svn_fs_fs__changes_list_t *changes = (svn_fs_fs__changes_list_t *)data;

  /* de-serialize our auxiliary data structure */
  svn_temp_deserializer__resolve(changes, (void**)&changes->changes);

  /* de-serialize each entry and add it to the array */
  for (i = 0; i < changes->count; ++i)
    deserialize_change(changes->changes,
                       (change_t **)&changes->changes[i]);

  /* done */
  *out = changes;

  return SVN_NO_ERROR;
}