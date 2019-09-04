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

int valid_binlog_path (char *path) {
  int i = 0;
  char *ptr = path;
  if (!*path || *path == '/' || *path == '.') {
    return 0;
  }
  while (*ptr) {
    if (!(*ptr == '/' || *ptr == '.' || *ptr == '-' || *ptr == '_' || (*ptr >= '0' && *ptr <= '9') || (*ptr >= 'a' && *ptr <= 'z') || (*ptr >= 'A' && *ptr <= 'Z'))) {
      return 0;
    }
    if (*ptr == '.' && (ptr[-1] == '.' || ptr[-1] == '/' || ptr[-1] == '_' || ptr[-1] == '-')) {
      return 0;
    }
    ptr++;
    i++;
  }
  if (i >= 64 || ptr[-1] == '.' || ptr[-1] == '/') {
    return 0;
  }
  return 1;
}