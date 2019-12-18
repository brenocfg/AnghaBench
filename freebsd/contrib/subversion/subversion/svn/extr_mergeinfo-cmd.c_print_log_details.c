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
struct TYPE_4__ {int /*<<< orphan*/ * changed_paths2; int /*<<< orphan*/ * changed_paths; } ;
typedef  TYPE_1__ svn_log_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_cl__log_entry_receiver (void*,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
print_log_details(void *baton,
                  svn_log_entry_t *log_entry,
                  apr_pool_t *pool)
{
  log_entry->changed_paths = NULL;
  log_entry->changed_paths2 = NULL;

  return svn_cl__log_entry_receiver(baton, log_entry, pool);
}