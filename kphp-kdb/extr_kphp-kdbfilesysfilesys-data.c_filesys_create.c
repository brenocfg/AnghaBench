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
struct filesys_inode {int reference_count; int index_offset; scalar_t__ index_filesize; scalar_t__ filesize; int /*<<< orphan*/  modification_time; } ;
struct filesys_directory_node {int mode; unsigned short uid; unsigned short gid; int inode; } ;
typedef  int inode_id_t ;

/* Variables and functions */
 int S_IFREG ; 
 int /*<<< orphan*/  cur_inode ; 
 struct filesys_directory_node* filesys_lookup_file (char const*,int /*<<< orphan*/ ) ; 
 struct filesys_inode* get_inode_f (int,int) ; 
 int /*<<< orphan*/  lf_creat ; 
 int /*<<< orphan*/  lf_find ; 
 int /*<<< orphan*/  now ; 
 int /*<<< orphan*/  vkprintf (int,char*,char const*,int,unsigned short,unsigned short,int) ; 

__attribute__((used)) static inode_id_t filesys_create (const char *path, int mode, unsigned short uid, unsigned short gid) {
  struct filesys_directory_node *F = filesys_lookup_file (path, lf_find);
  if (F != NULL) {
    return -3;
  }
  F = filesys_lookup_file (path, lf_creat);
  if (F == NULL) {
    return -2;
  }
  F->mode = mode | S_IFREG;
  F->uid = uid;
  F->gid = gid;
  F->inode = cur_inode++;

  vkprintf (2, "creat: %s, mode = %o, uid = %d, gid = %d, inode = %lld\n", path, mode, uid, gid, F->inode);

  struct filesys_inode *I = get_inode_f (F->inode, 1);
  I->reference_count = 1;
  I->modification_time = now;
  I->filesize = I->index_filesize = 0;
  I->index_offset = -1;
  return F->inode;
}