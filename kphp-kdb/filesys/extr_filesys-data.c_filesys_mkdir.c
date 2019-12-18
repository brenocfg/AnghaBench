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
struct filesys_directory_node {int mode; unsigned short uid; unsigned short gid; } ;

/* Variables and functions */
 int ENOENT ; 
 int S_IFDIR ; 
 struct filesys_directory_node* filesys_lookup_file (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lf_creat ; 

__attribute__((used)) static int filesys_mkdir (const char *path, int mode, unsigned short uid, unsigned short gid) {
  struct filesys_directory_node *D = filesys_lookup_file (path, lf_creat);
  if (D == NULL) {
    return -ENOENT;
  }
  D->mode = mode | S_IFDIR;
  D->uid = uid;
  D->gid = gid;
  return (D != NULL) ? 0 : -ENOENT;
}