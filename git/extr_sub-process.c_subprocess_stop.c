#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  pid; scalar_t__ clean_on_exit; } ;
struct subprocess_entry {int /*<<< orphan*/  ent; TYPE_1__ process; } ;
struct hashmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  finish_command (TYPE_1__*) ; 
 int /*<<< orphan*/  hashmap_remove (struct hashmap*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void subprocess_stop(struct hashmap *hashmap, struct subprocess_entry *entry)
{
	if (!entry)
		return;

	entry->process.clean_on_exit = 0;
	kill(entry->process.pid, SIGTERM);
	finish_command(&entry->process);

	hashmap_remove(hashmap, &entry->ent, NULL);
}