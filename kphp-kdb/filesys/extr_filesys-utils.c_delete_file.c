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
struct stat {int dummy; } ;

/* Variables and functions */
 scalar_t__ lstat (char const*,struct stat*) ; 
 int rec_delete_file (char const*,struct stat*) ; 

int delete_file (const char *path) {
  struct stat b;
  if (lstat (path, &b)) {
    return -1;
  }
  return rec_delete_file (path, &b);
}