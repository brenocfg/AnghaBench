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
struct filesys_inode {int /*<<< orphan*/ * updates; scalar_t__ index_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  filesys_inode_unload (struct filesys_inode*) ; 
 int /*<<< orphan*/  free_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tot_inodes ; 
 int /*<<< orphan*/  zfree (struct filesys_inode*,int) ; 

__attribute__((used)) static void free_inode (struct filesys_inode *I) {
  if (I->index_data) {
    filesys_inode_unload (I);
  }
  free_tree (I->updates);
  I->updates = NULL;
  tot_inodes--;
  zfree (I, sizeof (struct filesys_inode));
}