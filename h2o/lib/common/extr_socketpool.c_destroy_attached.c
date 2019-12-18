#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pool_entry_t {int /*<<< orphan*/  target_link; int /*<<< orphan*/  all_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_detached (struct pool_entry_t*) ; 
 int /*<<< orphan*/  h2o_linklist_unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_attached(struct pool_entry_t *entry)
{
    h2o_linklist_unlink(&entry->all_link);
    h2o_linklist_unlink(&entry->target_link);
    destroy_detached(entry);
}