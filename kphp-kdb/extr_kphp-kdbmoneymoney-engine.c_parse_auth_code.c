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

int parse_auth_code (char *ptr) {
  int i;

  for (i = 0; i < 32; i++) {
    if ((ptr[i] < 'a' && ptr[i] > '9') || ptr[i] < '0' || ptr[i] > 'f') {
      return 0;
    }
  }

  return 32;
}