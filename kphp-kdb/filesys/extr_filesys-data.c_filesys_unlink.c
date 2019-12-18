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
struct filesys_inode {scalar_t__ reference_count; } ;
struct filesys_directory_node {int /*<<< orphan*/  inode; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOENT ; 
 int /*<<< orphan*/  filesys_directory_node_free (struct filesys_directory_node*) ; 
 struct filesys_directory_node* filesys_lookup_file (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_inode (struct filesys_inode*) ; 
 struct filesys_inode* get_inode_f (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lf_unlink ; 
 int /*<<< orphan*/  vkprintf (int,char*,char const*) ; 

__attribute__((used)) static int filesys_unlink (const char *path) {
  vkprintf (2, "filesys_unlink (%s)\n", path);
  struct filesys_directory_node *D = filesys_lookup_file (path, lf_unlink);
  if (D == NULL) { return -ENOENT; }
  struct filesys_inode *I = get_inode_f (D->inode, -1);
  if (I == NULL) { return -EFAULT; }
  if (I->reference_count <= 0) {
    free_inode (I);
  }
  filesys_directory_node_free (D);
  return 0;
}