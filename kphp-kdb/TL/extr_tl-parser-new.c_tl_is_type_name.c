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

int tl_is_type_name (const char *id, int len) {
  if (len == 1 && *id == '#') { return 1;}
  int ok = id[0] >= 'A' && id[0] <= 'Z';
  int i;
  for (i = 0; i < len - 1; i++) if (id[i] == '.') {
    ok = id[i + 1] >= 'A' && id[i + 1] <= 'Z';
  }
  return ok;
}