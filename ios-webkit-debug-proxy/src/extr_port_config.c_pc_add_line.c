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
typedef  int /*<<< orphan*/  pc_t ;

/* Variables and functions */
 int /*<<< orphan*/  pc_add (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ pc_parse (int /*<<< orphan*/ ,char const*,int,char**,int*,int*) ; 

const char *pc_add_line(pc_t self, const char *line, size_t len) {
  const char *curr = line;
  const char *stop = line + len;
  while (curr < stop) {
    while (curr < stop && (*curr == ' ' || *curr == '\t')) {
      curr++;
    }
    const char *end = curr;
    while (end < stop &&
        *end && *end != '\n' && *end != '#' && *end != ',') {
      end++;
    }
    if (curr < end) {
      char *device_id;
      int min_port;
      int max_port;
      if (pc_parse(self, curr, end - curr,
            &device_id, &min_port, &max_port)) {
        return curr;
      }
      pc_add(self, device_id, min_port, max_port);
    }
    if (*end != ',') break;
    curr = end+1;
  }
  return NULL;
}