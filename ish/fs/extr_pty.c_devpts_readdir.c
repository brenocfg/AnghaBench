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
struct TYPE_2__ {int num; } ;
struct fd {int offset; TYPE_1__ devpts; } ;
struct dir_entry {int inode; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int MAX_PTYS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  devpts_pty_exists (int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int devpts_readdir(struct fd *fd, struct dir_entry *entry) {
    assert(fd->devpts.num == -1); // there shouldn't be anything to list but the root

    int pty_num = fd->offset;
    while (pty_num < MAX_PTYS && !devpts_pty_exists(pty_num))
        pty_num++;
    if (pty_num >= MAX_PTYS)
        return 0;
    fd->offset = pty_num + 1;
    sprintf(entry->name, "%d", pty_num);
    entry->inode = pty_num + 3;
    return 1;
}