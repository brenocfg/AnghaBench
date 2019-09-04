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
struct filesys_directory_node {unsigned short uid; unsigned short gid; } ;

/* Variables and functions */
 int EACCES ; 
 int ENOENT ; 
 struct filesys_directory_node* filesys_lookup_file (char const*,int /*<<< orphan*/ ) ; 
 unsigned short geteuid () ; 
 int /*<<< orphan*/  lf_find ; 

__attribute__((used)) static int filesys_chown (const char *path, unsigned short uid, unsigned short gid) {
  struct filesys_directory_node *D = filesys_lookup_file (path, lf_find);
  if (D == NULL) {
    return -ENOENT;
  }
  if (geteuid () && geteuid () != D->uid) {
    return -EACCES;
  }
  D->uid = uid;
  D->gid = gid;
  return 0;
}