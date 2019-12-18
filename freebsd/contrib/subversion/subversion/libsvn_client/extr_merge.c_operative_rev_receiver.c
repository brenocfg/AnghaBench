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
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_3__ {int /*<<< orphan*/  revision; } ;
typedef  TYPE_1__ svn_log_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_CEASE_INVOCATION ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
operative_rev_receiver(void *baton,
                       svn_log_entry_t *log_entry,
                       apr_pool_t *pool)
{
  svn_revnum_t *operative_rev = baton;

  *operative_rev = log_entry->revision;

  /* We've found the youngest merged or oldest eligible revision, so
     we're done...

     ...but wait, shouldn't we care if LOG_ENTRY->NON_INHERITABLE is
     true?  Because if it is, then LOG_ENTRY->REVISION is only
     partially merged/elgibile!  And our only caller,
     find_last_merged_location (via short_circuit_mergeinfo_log) is
     interested in *fully* merged revisions.  That's all true, but if
     find_last_merged_location() finds the youngest merged revision it
     will also check for the oldest eligible revision.  So in the case
     the youngest merged rev is non-inheritable, the *same* non-inheritable
     rev will be found as the oldest eligible rev -- and
     find_last_merged_location() handles that situation. */
  return svn_error_create(SVN_ERR_CEASE_INVOCATION, NULL, NULL);
}