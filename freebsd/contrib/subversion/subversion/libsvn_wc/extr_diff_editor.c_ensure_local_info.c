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
struct dir_baton_t {int /*<<< orphan*/  pool; int /*<<< orphan*/  local_abspath; TYPE_1__* eb; scalar_t__ local_info; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_2__ {int /*<<< orphan*/  db; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_wc__db_read_children_info (scalar_t__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
ensure_local_info(struct dir_baton_t *db,
                  apr_pool_t *scratch_pool)
{
  apr_hash_t *conflicts;

  if (db->local_info)
    return SVN_NO_ERROR;

  SVN_ERR(svn_wc__db_read_children_info(&db->local_info, &conflicts,
                                        db->eb->db, db->local_abspath,
                                        FALSE /* base_tree_only */,
                                        db->pool, scratch_pool));

  return SVN_NO_ERROR;
}