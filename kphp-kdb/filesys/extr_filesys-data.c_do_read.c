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
struct filesys_directory_node {scalar_t__ inode; } ;

/* Variables and functions */
 struct filesys_directory_node* filesys_lookup_file (char const*,int /*<<< orphan*/ ) ; 
 int filesys_read (struct filesys_inode*,unsigned int,unsigned int,char*) ; 
 struct filesys_inode* get_inode_f (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lf_find ; 
 int /*<<< orphan*/  vkprintf (int,char*,scalar_t__) ; 

int do_read (unsigned int offset, unsigned int size, const char *filename, char *output) {
  struct filesys_directory_node *D = filesys_lookup_file (filename, lf_find);
  if (D == NULL) { return -1; }
  if (D->inode < 0) { return -2; }
  struct filesys_inode *I = get_inode_f (D->inode, 0);
  if (I == NULL) { return -3; }

  vkprintf (3, "do_read: inode = %lld\n", D->inode);

  return filesys_read (I, offset, size, output);
}