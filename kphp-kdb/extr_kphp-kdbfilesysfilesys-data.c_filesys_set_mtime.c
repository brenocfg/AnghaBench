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
struct filesys_directory_node {int modification_time; } ;

/* Variables and functions */
 int ENOENT ; 
 struct filesys_directory_node* filesys_lookup_file (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lf_find ; 

__attribute__((used)) static int filesys_set_mtime (const char *path, int modification_time) {
  struct filesys_directory_node *D = filesys_lookup_file (path, lf_find);
  if (D == NULL) {
    return -ENOENT;
  }
  D->modification_time = modification_time;
  return 0;
}