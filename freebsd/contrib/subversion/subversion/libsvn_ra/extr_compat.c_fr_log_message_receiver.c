#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  revision; int /*<<< orphan*/  changed_paths2; int /*<<< orphan*/  revprops; } ;
typedef  TYPE_1__ svn_log_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct rev {int /*<<< orphan*/  props; struct rev* next; int /*<<< orphan*/  path; int /*<<< orphan*/  revision; } ;
struct fr_log_message_baton {int /*<<< orphan*/  pool; int /*<<< orphan*/  path; int /*<<< orphan*/  copyrev; int /*<<< orphan*/  action; struct rev* eldest; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 struct rev* apr_palloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * prev_log_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_node_file ; 
 int /*<<< orphan*/  svn_prop_hash_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
fr_log_message_receiver(void *baton,
                        svn_log_entry_t *log_entry,
                        apr_pool_t *pool)
{
  struct fr_log_message_baton *lmb = baton;
  struct rev *rev;

  rev = apr_palloc(lmb->pool, sizeof(*rev));
  rev->revision = log_entry->revision;
  rev->path = lmb->path;
  rev->next = lmb->eldest;
  lmb->eldest = rev;

  /* Duplicate log_entry revprops into rev->props */
  rev->props = svn_prop_hash_dup(log_entry->revprops, lmb->pool);

  return prev_log_path(&lmb->path, &lmb->action,
                       &lmb->copyrev, log_entry->changed_paths2,
                       lmb->path, svn_node_file, log_entry->revision,
                       lmb->pool);
}