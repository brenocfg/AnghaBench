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
typedef  int /*<<< orphan*/  svn_fs_path_change_kind_t ;
struct TYPE_4__ {int /*<<< orphan*/  copyfrom_rev; int /*<<< orphan*/  mergeinfo_mod; int /*<<< orphan*/  change_kind; int /*<<< orphan*/  const* node_rev_id; } ;
typedef  TYPE_1__ svn_fs_path_change2_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_tristate_unknown ; 

svn_fs_path_change2_t *
svn_fs__path_change_create_internal(const svn_fs_id_t *node_rev_id,
                                    svn_fs_path_change_kind_t change_kind,
                                    apr_pool_t *pool)
{
  svn_fs_path_change2_t *change;

  change = apr_pcalloc(pool, sizeof(*change));
  change->node_rev_id = node_rev_id;
  change->change_kind = change_kind;
  change->mergeinfo_mod = svn_tristate_unknown;
  change->copyfrom_rev = SVN_INVALID_REVNUM;

  return change;
}