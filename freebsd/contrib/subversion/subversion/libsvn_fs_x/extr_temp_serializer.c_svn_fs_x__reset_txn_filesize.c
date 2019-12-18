#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_2__ {int /*<<< orphan*/  txn_filesize; } ;
typedef  TYPE_1__ dir_data_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_INVALID_FILESIZE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 

svn_error_t *
svn_fs_x__reset_txn_filesize(void **data,
                             apr_size_t *data_len,
                             void *baton,
                             apr_pool_t *pool)
{
  dir_data_t *dir_data = (dir_data_t *)*data;
  dir_data->txn_filesize = SVN_INVALID_FILESIZE;

  return SVN_NO_ERROR;
}