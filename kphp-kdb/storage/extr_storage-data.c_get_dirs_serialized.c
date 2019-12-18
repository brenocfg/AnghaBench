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

/* Variables and functions */
 scalar_t__ Dirs ; 
 int dirs ; 
 int /*<<< orphan*/  get_dir_serialized (char*,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

int get_dirs_serialized (char *buffer) {
  int i;
  char *p = buffer;
  p += sprintf (p, "a:%d:{", dirs);
  for (i = 0; i < dirs; i++) {
    p += sprintf (p, "i:%d;", i);
    p += get_dir_serialized (p, Dirs + i);
  }
  p += sprintf (p, "}");
  return 0;
}