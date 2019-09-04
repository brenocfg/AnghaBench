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
struct stat {scalar_t__ st_mode; scalar_t__ st_uid; scalar_t__ st_gid; scalar_t__ st_size; scalar_t__ st_mtime; } ;

/* Variables and functions */

__attribute__((used)) static int get_changed_attrs (struct stat *a, struct stat *b) {
  int attrib_mask = 0;
  if (a->st_mode != b->st_mode) {
    attrib_mask |= 1;
  }
  if (a->st_uid != b->st_uid) {
    attrib_mask |= 2;
  }
  if (a->st_gid != b->st_gid) {
    attrib_mask |= 4;
  }
  if (a->st_size != b->st_size) {
    attrib_mask |= 8;
  }
  if (a->st_mtime != b->st_mtime) {
    attrib_mask |= 16;
  }
  return attrib_mask;
}