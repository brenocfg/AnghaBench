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
struct TYPE_4__ {int /*<<< orphan*/  revision; } ;
typedef  TYPE_1__ svn_commit_info_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 

svn_commit_info_t *
svn_create_commit_info(apr_pool_t *pool)
{
  svn_commit_info_t *commit_info
    = apr_pcalloc(pool, sizeof(*commit_info));

  commit_info->revision = SVN_INVALID_REVNUM;
  /* All other fields were initialized to NULL above. */

  return commit_info;
}