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
struct filesys_directory_node {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  filesys_directory_node_free (struct filesys_directory_node*) ; 
 struct filesys_directory_node* filesys_lookup_file (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lf_rmdir ; 

__attribute__((used)) static int filesys_rmdir (const char *path) {
  struct filesys_directory_node *D = filesys_lookup_file (path, lf_rmdir);
  if (D == NULL) {
    return -ENOENT;
  }
  filesys_directory_node_free (D);
  return 0;
}