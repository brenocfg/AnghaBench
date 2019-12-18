#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* data; } ;
struct TYPE_6__ {int /*<<< orphan*/  copyfrom_rev; int /*<<< orphan*/  mergeinfo_mod; int /*<<< orphan*/  change_kind; TYPE_1__ path; } ;
typedef  TYPE_2__ svn_repos_path_change_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_fs_path_change_reset ; 
 int /*<<< orphan*/  svn_tristate_unknown ; 

svn_repos_path_change_t *
svn_repos_path_change_create(apr_pool_t *result_pool)
{
  svn_repos_path_change_t *change = apr_pcalloc(result_pool, sizeof(*change));

  change->path.data = "";
  change->change_kind = svn_fs_path_change_reset;
  change->mergeinfo_mod = svn_tristate_unknown;
  change->copyfrom_rev = SVN_INVALID_REVNUM;

  return change;
}