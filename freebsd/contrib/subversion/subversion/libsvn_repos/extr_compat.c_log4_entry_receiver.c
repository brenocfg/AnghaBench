#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  subtractive_merge; int /*<<< orphan*/  non_inheritable; int /*<<< orphan*/  has_children; int /*<<< orphan*/  revprops; int /*<<< orphan*/  revision; } ;
typedef  TYPE_1__ svn_repos_log_entry_t ;
struct TYPE_8__ {int /*<<< orphan*/  subtractive_merge; int /*<<< orphan*/  non_inheritable; int /*<<< orphan*/ * changed_paths2; int /*<<< orphan*/  has_children; int /*<<< orphan*/  revprops; int /*<<< orphan*/  revision; int /*<<< orphan*/ * changed_paths; } ;
typedef  TYPE_2__ svn_log_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_9__ {int /*<<< orphan*/ * changes; int /*<<< orphan*/  changes_pool; int /*<<< orphan*/  inner_baton; int /*<<< orphan*/  (* inner ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ log_entry_receiver_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_log_entry_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
log4_entry_receiver(void *baton,
                    svn_repos_log_entry_t *log_entry,
                    apr_pool_t *scratch_pool)
{
  log_entry_receiver_baton_t *b = baton;
  svn_log_entry_t *entry = svn_log_entry_create(scratch_pool);

  /* Complete the ENTRY. */
  entry->changed_paths = b->changes;
  entry->revision = log_entry->revision;
  entry->revprops = log_entry->revprops;
  entry->has_children = log_entry->has_children;
  entry->changed_paths2 = b->changes;
  entry->non_inheritable = log_entry->non_inheritable;
  entry->subtractive_merge = log_entry->subtractive_merge;

  /* Invoke the log4-compatible callback. */
  SVN_ERR(b->inner(b->inner_baton, entry, scratch_pool));

  /* Release per-revision data. */
  svn_pool_clear(b->changes_pool);
  b->changes = NULL;

  return SVN_NO_ERROR;
}