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
struct proc_entry {TYPE_1__* meta; } ;
struct TYPE_2__ {scalar_t__ name; int /*<<< orphan*/  (* getname ) (struct proc_entry*,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  strcpy (char*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct proc_entry*,char*) ; 

void proc_entry_getname(struct proc_entry *entry, char *buf) {
    if (entry->meta->getname)
        entry->meta->getname(entry, buf);
    else if (entry->meta->name)
        strcpy(buf, entry->meta->name);
    else
        assert(!"missing name in proc entry");
}