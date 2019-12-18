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
struct filesys_inode {scalar_t__ index_offset; long index_filesize; int /*<<< orphan*/ * index_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  add_use (struct filesys_inode*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  del_use (struct filesys_inode*) ; 
 int /*<<< orphan*/  filesys_inode_unload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idx_fd ; 
 int /*<<< orphan*/  lru_head ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (long) ; 
 scalar_t__ max_loaded_index_data ; 
 long read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,long) ; 
 scalar_t__ tot_loaded_index_data ; 
 int tot_loaded_metafiles ; 

__attribute__((used)) static void filesys_inode_load (struct filesys_inode *I) {
  if (I->index_offset < 0) {
    return;
  }

  if (I->index_data != NULL) {
    del_use (I);
    add_use (I);
    return;
  }

  I->index_data = malloc (I->index_filesize);
  assert (lseek (idx_fd, I->index_offset, SEEK_SET) >= 0);
  long r = read (idx_fd, I->index_data, I->index_filesize);
  assert (r == I->index_filesize);
  tot_loaded_index_data += I->index_filesize;
  tot_loaded_metafiles++;
  add_use (I);
  while (tot_loaded_metafiles > 1 && tot_loaded_index_data > max_loaded_index_data) {
    filesys_inode_unload (lru_head);
  }
}