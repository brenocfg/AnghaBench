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
 int rec_clone_file (char const* const,char const* const,char*,struct stat*) ; 
 scalar_t__ stat (char const* const,struct stat*) ; 

int clone_file (const char *const oldpath, const char *const newpath) {
  struct stat b;
  if (stat (oldpath, &b)) {
    return -1;
  }
  return rec_clone_file (oldpath, newpath, "", &b);
}