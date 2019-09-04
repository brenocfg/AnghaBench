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
struct TYPE_2__ {scalar_t__ scanned; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 TYPE_1__* Dirs ; 
 int /*<<< orphan*/  kprintf (char*,int,int) ; 
 int storage_scan_dir (int) ; 
 int /*<<< orphan*/  zstrdup (char const* const) ; 

void scan_dir (const char *const path, int dir_id) {
  Dirs[dir_id].path = zstrdup (path);
  Dirs[dir_id].scanned = 0;
  int r = storage_scan_dir (dir_id);
  if (r < 0) {
    kprintf ("storage_scan_dir (%d) returns error code %d.\n", dir_id, r);
  }
}