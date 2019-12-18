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
struct TYPE_3__ {int /*<<< orphan*/ * fsap_data; } ;
typedef  TYPE_1__ svn_fs_path_change_iterator_t ;
typedef  int /*<<< orphan*/  svn_fs_path_change3_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_this_val (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
x_txn_changes_iterator_get(svn_fs_path_change3_t **change,
                           svn_fs_path_change_iterator_t *iterator)
{
  apr_hash_index_t *hi = iterator->fsap_data;

  if (hi)
    {
      *change = apr_hash_this_val(hi);
      iterator->fsap_data = apr_hash_next(hi);
    }
  else
    {
      *change = NULL;
    }

  return SVN_NO_ERROR;
}