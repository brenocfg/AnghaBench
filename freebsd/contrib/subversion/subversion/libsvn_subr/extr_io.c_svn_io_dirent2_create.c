#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  filesize; } ;
typedef  TYPE_1__ svn_io_dirent2_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_INVALID_FILESIZE ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 

svn_io_dirent2_t *
svn_io_dirent2_create(apr_pool_t *result_pool)
{
  svn_io_dirent2_t *dirent = apr_pcalloc(result_pool, sizeof(*dirent));

  /*dirent->kind = svn_node_none;
  dirent->special = FALSE;*/
  dirent->filesize = SVN_INVALID_FILESIZE;
  /*dirent->mtime = 0;*/

  return dirent;
}