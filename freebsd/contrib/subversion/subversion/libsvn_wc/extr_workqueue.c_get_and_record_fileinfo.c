#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  result_pool; scalar_t__ record_map; int /*<<< orphan*/  used; } ;
typedef  TYPE_1__ work_item_baton_t ;
struct TYPE_7__ {scalar_t__ kind; } ;
typedef  TYPE_2__ svn_io_dirent2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ apr_hash_make (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (scalar_t__,int /*<<< orphan*/ ,TYPE_2__ const*) ; 
 int /*<<< orphan*/  svn_io_stat_dirent2 (TYPE_2__ const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 

__attribute__((used)) static svn_error_t *
get_and_record_fileinfo(work_item_baton_t *wqb,
                        const char *local_abspath,
                        svn_boolean_t ignore_enoent,
                        apr_pool_t *scratch_pool)
{
  const svn_io_dirent2_t *dirent;

  SVN_ERR(svn_io_stat_dirent2(&dirent, local_abspath, FALSE, ignore_enoent,
                              wqb->result_pool, scratch_pool));

  if (dirent->kind != svn_node_file)
    return SVN_NO_ERROR;

  wqb->used = TRUE;

  if (! wqb->record_map)
    wqb->record_map = apr_hash_make(wqb->result_pool);

  svn_hash_sets(wqb->record_map, apr_pstrdup(wqb->result_pool, local_abspath),
                dirent);

  return SVN_NO_ERROR;
}