#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 TYPE_1__* Dirs ; 
 int dirs ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const* const) ; 

int get_dir_id_by_name (const char *const dirname) {
  int i;
  for (i = 0; i < dirs; i++) {
    if (!strcmp (Dirs[i].path, dirname)) {
      return i;
    }
  }
  return -1;
}