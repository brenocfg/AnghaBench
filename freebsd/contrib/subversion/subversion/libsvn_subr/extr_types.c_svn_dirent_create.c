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
struct TYPE_4__ {int /*<<< orphan*/ * last_author; scalar_t__ time; int /*<<< orphan*/  created_rev; int /*<<< orphan*/  size; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ svn_dirent_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_INVALID_FILESIZE ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_node_unknown ; 

svn_dirent_t *
svn_dirent_create(apr_pool_t *result_pool)
{
  svn_dirent_t *new_dirent = apr_pcalloc(result_pool, sizeof(*new_dirent));

  new_dirent->kind = svn_node_unknown;
  new_dirent->size = SVN_INVALID_FILESIZE;
  new_dirent->created_rev = SVN_INVALID_REVNUM;
  new_dirent->time = 0;
  new_dirent->last_author = NULL;

  return new_dirent;
}