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
struct TYPE_4__ {int /*<<< orphan*/  reason; int /*<<< orphan*/  action; int /*<<< orphan*/  kind; int /*<<< orphan*/  node_kind; int /*<<< orphan*/  local_abspath; } ;
typedef  TYPE_1__ svn_wc_conflict_description2_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int /*<<< orphan*/ ) ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_node_file ; 
 int /*<<< orphan*/  svn_wc_conflict_action_edit ; 
 int /*<<< orphan*/  svn_wc_conflict_kind_text ; 
 int /*<<< orphan*/  svn_wc_conflict_reason_edited ; 

svn_wc_conflict_description2_t *
svn_wc_conflict_description_create_text2(const char *local_abspath,
                                         apr_pool_t *result_pool)
{
  svn_wc_conflict_description2_t *conflict;

  SVN_ERR_ASSERT_NO_RETURN(svn_dirent_is_absolute(local_abspath));

  conflict = apr_pcalloc(result_pool, sizeof(*conflict));
  conflict->local_abspath = apr_pstrdup(result_pool, local_abspath);
  conflict->node_kind = svn_node_file;
  conflict->kind = svn_wc_conflict_kind_text;
  conflict->action = svn_wc_conflict_action_edit;
  conflict->reason = svn_wc_conflict_reason_edited;
  return conflict;
}