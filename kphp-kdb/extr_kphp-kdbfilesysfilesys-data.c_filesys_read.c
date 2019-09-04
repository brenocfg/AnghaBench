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
struct filesys_inode {unsigned int index_filesize; int /*<<< orphan*/ * index_data; } ;

/* Variables and functions */
 unsigned int copy_updates (struct filesys_inode*,unsigned int,unsigned int,char*,unsigned int*) ; 
 int /*<<< orphan*/  filesys_inode_load (struct filesys_inode*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 

__attribute__((used)) static int filesys_read (struct filesys_inode *I, unsigned int offset, unsigned int length, char *data) {
  unsigned int blocksize;
  memset (data, 0, length);
  if (copy_updates (I, offset, length, data, &blocksize) == length) {
    return length;
  }

  vkprintf (3, "filesys_read: before memset\n");

  if (offset >= I->index_filesize) {
    /* avoid loading metafile, if we really doesn't need it */
    return blocksize;
  }
  filesys_inode_load (I);
  if (I->index_data) {
    unsigned int moved_bytes = I->index_filesize - offset;
    if (moved_bytes > length) {
      moved_bytes = length;
    }
    memcpy (data, &I->index_data[offset], moved_bytes);
    if (blocksize < moved_bytes) {
      blocksize = moved_bytes;
    }
  }
  unsigned int tmp;
  copy_updates (I, offset, length, data, &tmp);
  return blocksize;
}