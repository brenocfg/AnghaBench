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
 scalar_t__ isdigit (char const) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

int pmemcache_match_stats_key (const char *key, int key_len) {
  if (key_len < 5 || strncmp (key, "stats", 5)) { return 0; }
  if (key_len == 5) {
    return 1;
  }
  if (key_len >= 10 && key[5] == '#' && key[key_len - 1] == '$' && key[key_len - 2] == '#' && key[key_len - 3] == '@') {
    int i = 6, j;
    if (key[i] == '-') {
      i++;
    }
    for (j = i; isdigit (key[j]); j++) {}
    if (i < j && j == key_len - 3) { return 1; }
  }
  return 0;
}