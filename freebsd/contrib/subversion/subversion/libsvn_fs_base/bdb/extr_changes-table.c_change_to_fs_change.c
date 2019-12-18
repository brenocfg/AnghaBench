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
struct TYPE_6__ {int /*<<< orphan*/  copyfrom_known; int /*<<< orphan*/  node_kind; int /*<<< orphan*/  prop_mod; int /*<<< orphan*/  text_mod; } ;
typedef  TYPE_1__ svn_fs_path_change2_t ;
struct TYPE_7__ {int /*<<< orphan*/  prop_mod; int /*<<< orphan*/  text_mod; int /*<<< orphan*/  kind; int /*<<< orphan*/  noderev_id; } ;
typedef  TYPE_2__ change_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* svn_fs__path_change_create_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_base__id_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_unknown ; 

__attribute__((used)) static svn_fs_path_change2_t *
change_to_fs_change(const change_t *change,
                    apr_pool_t *result_pool)
{
  svn_fs_path_change2_t *result = svn_fs__path_change_create_internal(
                                    svn_fs_base__id_copy(change->noderev_id,
                                                         result_pool),
                                    change->kind,
                                    result_pool);
  result->text_mod = change->text_mod;
  result->prop_mod = change->prop_mod;
  result->node_kind = svn_node_unknown;
  result->copyfrom_known = FALSE;

  return result;
}