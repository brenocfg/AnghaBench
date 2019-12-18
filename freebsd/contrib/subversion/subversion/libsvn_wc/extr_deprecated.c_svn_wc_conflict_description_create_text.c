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
struct TYPE_4__ {char const* path; int /*<<< orphan*/  reason; int /*<<< orphan*/  action; int /*<<< orphan*/ * access; int /*<<< orphan*/  kind; int /*<<< orphan*/  node_kind; } ;
typedef  TYPE_1__ svn_wc_conflict_description_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_node_file ; 
 int /*<<< orphan*/  svn_wc_conflict_action_edit ; 
 int /*<<< orphan*/  svn_wc_conflict_kind_text ; 
 int /*<<< orphan*/  svn_wc_conflict_reason_edited ; 

svn_wc_conflict_description_t *
svn_wc_conflict_description_create_text(const char *path,
                                        svn_wc_adm_access_t *adm_access,
                                        apr_pool_t *pool)
{
  svn_wc_conflict_description_t *conflict;

  conflict = apr_pcalloc(pool, sizeof(*conflict));
  conflict->path = path;
  conflict->node_kind = svn_node_file;
  conflict->kind = svn_wc_conflict_kind_text;
  conflict->access = adm_access;
  conflict->action = svn_wc_conflict_action_edit;
  conflict->reason = svn_wc_conflict_reason_edited;
  return conflict;
}