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
struct ish_stat {int dummy; } ;
struct fd {int /*<<< orphan*/  mount; int /*<<< orphan*/  fake_inode; } ;
struct attr {scalar_t__ type; } ;
struct TYPE_2__ {int (* fsetattr ) (struct fd*,struct attr) ;} ;

/* Variables and functions */
 scalar_t__ attr_size ; 
 int /*<<< orphan*/  db_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fake_stat_setattr (struct ish_stat*,struct attr) ; 
 int /*<<< orphan*/  inode_read_stat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ish_stat*) ; 
 int /*<<< orphan*/  inode_write_stat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ish_stat*) ; 
 TYPE_1__ realfs ; 
 int stub1 (struct fd*,struct attr) ; 

__attribute__((used)) static int fakefs_fsetattr(struct fd *fd, struct attr attr) {
    if (attr.type == attr_size)
        return realfs.fsetattr(fd, attr);
    db_begin(fd->mount);
    struct ish_stat ishstat;
    inode_read_stat(fd->mount, fd->fake_inode, &ishstat);
    fake_stat_setattr(&ishstat, attr);
    inode_write_stat(fd->mount, fd->fake_inode, &ishstat);
    db_commit(fd->mount);
    return 0;
}