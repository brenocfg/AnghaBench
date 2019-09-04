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
struct filesys_inode {int /*<<< orphan*/  reference_count; } ;
struct filesys_directory_node {scalar_t__ inode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  mode; } ;
typedef  scalar_t__ inode_id_t ;

/* Variables and functions */
 int EEXIST ; 
 int EFAULT ; 
 int ENOENT ; 
 struct filesys_directory_node* filesys_lookup_file (char const*,int /*<<< orphan*/ ) ; 
 struct filesys_inode* get_inode_f (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lf_creat ; 
 int /*<<< orphan*/  lf_find ; 
 int /*<<< orphan*/  vkprintf (int,char*,char const*,char const*) ; 

__attribute__((used)) static int filesys_link (const char *src_filename, const char *dest_filename) {
  vkprintf (2, "filesys_link (%s, %s)\n", src_filename, dest_filename);

  struct filesys_directory_node *E = filesys_lookup_file (dest_filename, lf_find);
  if (E != NULL) { return -EEXIST; }
  struct filesys_directory_node *D = filesys_lookup_file (src_filename, lf_find);
  if (D == NULL) { return -ENOENT; }
  if (D->inode < 0) { return -ENOENT; }
  inode_id_t inode = D->inode;
  struct filesys_inode *I = get_inode_f (inode, 0);
  if (I == NULL) { return -EFAULT; }
  E = filesys_lookup_file (dest_filename, lf_creat);
  if (E == NULL) { return -ENOENT; }
  I->reference_count++;
  E->inode = inode;
  E->mode = D->mode;
  E->uid = D->uid;
  E->gid = D->gid;
  return 0;
}