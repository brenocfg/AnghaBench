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
struct filesys_inode {int dummy; } ;
typedef  scalar_t__ inode_id_t ;

/* Variables and functions */
 int ENOENT ; 
 int S_IFLNK ; 
 scalar_t__ filesys_create (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filesys_write (struct filesys_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 struct filesys_inode* get_inode_f (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getgid () ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int filesys_symlink (const char *oldpath, const char *newpath) {
  inode_id_t inode = filesys_create (newpath, 0777 | S_IFLNK, getuid (), getgid ());
  if (inode < 0) {
    return -ENOENT;
  }
  struct filesys_inode *I = get_inode_f (inode, 0);
  filesys_write (I, 0, strlen (oldpath), oldpath);
  return 0;
}