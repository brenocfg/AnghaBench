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
struct proc_entry {int /*<<< orphan*/  pid; TYPE_1__* meta; } ;
struct TYPE_2__ {int (* readdir ) (struct proc_entry*,unsigned long*,struct proc_entry*) ;int children_sizeof; struct TYPE_2__* children; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int stub1 (struct proc_entry*,unsigned long*,struct proc_entry*) ; 

bool proc_dir_read(struct proc_entry *entry, unsigned long *index, struct proc_entry *next_entry) {
    if (entry->meta->readdir)
        return entry->meta->readdir(entry, index, next_entry);

    if (entry->meta->children) {
        if (*index >= entry->meta->children_sizeof/sizeof(entry->meta->children[0]))
            return false;
        next_entry->meta = &entry->meta->children[*index];
        next_entry->pid = entry->pid;
        (*index)++;
        return true;
    }
    assert(!"read from invalid proc directory");
}