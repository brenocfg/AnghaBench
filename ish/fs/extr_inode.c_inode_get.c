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
struct inode_data {size_t number; int /*<<< orphan*/  lock; scalar_t__ refcount; int /*<<< orphan*/  chain; int /*<<< orphan*/  posix_locks; int /*<<< orphan*/  posix_unlock; scalar_t__ socket_id; struct mount* mount; } ;
typedef  size_t ino_t ;

/* Variables and functions */
 size_t INODES_HASH_SIZE ; 
 int /*<<< orphan*/  cond_init (int /*<<< orphan*/ *) ; 
 struct inode_data* inode_get_data (struct mount*,size_t) ; 
 int /*<<< orphan*/ * inodes_hash ; 
 int /*<<< orphan*/  inodes_lock ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_init (int /*<<< orphan*/ *) ; 
 struct inode_data* malloc (int) ; 
 int /*<<< orphan*/  mount_retain (struct mount*) ; 
 int /*<<< orphan*/  unlock (int /*<<< orphan*/ *) ; 

struct inode_data *inode_get(struct mount *mount, ino_t ino) {
    lock(&inodes_lock);
    struct inode_data *inode = inode_get_data(mount, ino);
    if (inode == NULL) {
        inode = malloc(sizeof(struct inode_data));
        inode->refcount = 0;
        inode->number = ino;
        mount_retain(mount);
        inode->mount = mount;
        inode->socket_id = 0;
        cond_init(&inode->posix_unlock);
        list_init(&inode->posix_locks);
        list_init(&inode->chain);
        lock_init(&inode->lock);
        list_add(&inodes_hash[ino % INODES_HASH_SIZE], &inode->chain);
    }

    lock(&inode->lock);
    inode->refcount++;
    unlock(&inode->lock);
    unlock(&inodes_lock);
    return inode;
}