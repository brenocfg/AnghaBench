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
struct proc_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  entry; } ;
struct fd {int /*<<< orphan*/  offset; TYPE_1__ proc; } ;
struct dir_entry {scalar_t__ inode; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int proc_dir_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct proc_entry*) ; 
 int /*<<< orphan*/  proc_entry_getname (struct proc_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_readdir(struct fd *fd, struct dir_entry *entry) {
    struct proc_entry proc_entry;
    bool any_left = proc_dir_read(&fd->proc.entry, &fd->offset, &proc_entry);
    if (!any_left)
        return 0;
    proc_entry_getname(&proc_entry, entry->name);
    entry->inode = 0;
    return 1;
}