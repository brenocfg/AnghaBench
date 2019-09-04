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

int tftp_fetch_string (char *in, int avail_in) {
  int i = 0;
  while (i < avail_in && in[i]) {
    i++;
  }
  if (i >= avail_in) { return -1; }
  return i + 1;
}