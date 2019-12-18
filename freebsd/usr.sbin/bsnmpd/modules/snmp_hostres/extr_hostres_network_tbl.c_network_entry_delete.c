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
struct network_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct network_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct network_entry*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  network_tbl ; 

__attribute__((used)) static void
network_entry_delete(struct network_entry* entry)
{

	TAILQ_REMOVE(&network_tbl, entry, link);
	free(entry);
}