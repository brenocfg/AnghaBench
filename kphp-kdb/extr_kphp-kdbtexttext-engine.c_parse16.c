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
 int char_to_hex (int /*<<< orphan*/ ) ; 

int parse16 (const char *from, int len) {
  const char *from_end = from + len;
  int res = 0;
  while (from < from_end) {
    res = res * 16 + char_to_hex (*from++);
  }
  return res;
}