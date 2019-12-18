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
 char const* cur_key ; 
 int cur_key_len ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

int get_key (const char *cmd, int len) {
  const char *ptr = cmd, *to = cmd + len;

  if (!len) {
    return 0;
  }

  if (len < 5 || strncmp (cmd, "VALUE", 5)) {
    return 0;
  }
  ptr += 5;

  while (ptr < to && *ptr == ' ') {
    ptr++;
  }
  if (ptr >= to) {
    return 0;
  }
  const char *key = ptr;
  while (ptr < to && (unsigned char) *ptr > ' ') {
    ptr++;
  }
  if (ptr >= to) {
    return 0;
  }
  cur_key = key;
  cur_key_len = ptr - key;
  return 1;
}