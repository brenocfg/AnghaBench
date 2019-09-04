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
struct filesys_inode {scalar_t__ index_filesize; int /*<<< orphan*/ * index_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_use (struct filesys_inode*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tot_loaded_index_data ; 
 int /*<<< orphan*/  tot_loaded_metafiles ; 

__attribute__((used)) static void filesys_inode_unload (struct filesys_inode *I) {
  if (I->index_data == NULL) { return; }
  free (I->index_data);
  I->index_data = NULL;
  tot_loaded_index_data -= I->index_filesize;
  tot_loaded_metafiles--;
  del_use (I);
}