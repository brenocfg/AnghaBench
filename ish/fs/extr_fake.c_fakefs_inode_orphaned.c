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
struct mount {int dummy; } ;
struct inode_data {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  db_begin (struct mount*) ; 
 int /*<<< orphan*/  db_commit (struct mount*) ; 
 int /*<<< orphan*/  try_cleanup_inode (struct mount*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fakefs_inode_orphaned(struct mount *mount, struct inode_data *inode) {
    db_begin(mount);
    try_cleanup_inode(mount, inode->number);
    db_commit(mount);
}