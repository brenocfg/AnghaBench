#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pc_t ;
typedef  TYPE_1__* pc_entry_t ;
struct TYPE_3__ {int min_port; int max_port; } ;

/* Variables and functions */
 TYPE_1__* pc_find (int /*<<< orphan*/ ,char const*) ; 

int pc_select_port(pc_t self, const char *device_id,
    int *to_port, int *to_min_port, int *to_max_port) {
  const pc_entry_t config = pc_find(self, device_id);
  if (!config) {
    *to_min_port = -1;
    *to_max_port = -1;
    *to_port = -1;
    return -1;
  }
  *to_min_port = config->min_port;
  *to_max_port = config->max_port;
  if (*to_port >= 0 &&
      (*to_port < *to_min_port || *to_port > *to_max_port)) {
    *to_port = -1;
  }
  return 0;
}