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
struct inode_data {int dummy; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 struct inode_data* inode_get_data (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inodes_lock ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

bool inode_is_orphaned(struct mount *mount, ino_t ino) {
    lock(&inodes_lock);
    struct inode_data *inode = inode_get_data(mount, ino);
    unlock(&inodes_lock);
    return inode == NULL;
}