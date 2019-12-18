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
 int /*<<< orphan*/  cur_write_name ; 
 int log_split_mod ; 
 char* name_pattern ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int) ; 

void generate_write_name (int i) {
  int z = 2;
  if (log_split_mod > 100) {
    z = 3;
  }
  if (log_split_mod > 1000) {
    z = 4;
  }
  if (z == 2) {
    sprintf (cur_write_name, "%s%02d.bin", name_pattern, i);
  } else if (z == 3) {
    sprintf (cur_write_name, "%s%03d.bin", name_pattern, i);
  } else if (z == 4) {
    sprintf (cur_write_name, "%s%04d.bin", name_pattern, i);
  }
}