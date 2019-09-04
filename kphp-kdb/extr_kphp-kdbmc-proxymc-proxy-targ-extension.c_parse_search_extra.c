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
 char const* parse_search_extra_common (char const*,int,char,int*,int*) ; 

__attribute__((used)) static int parse_search_extra (const char *key, int key_len, int *limit, int *extra_start, int *extra_end) {
  int flags;
  int search = (key[key_len - 1] == ')');
  if (search) {
    int t = key_len - 1;
    while (t >= 0 && key[t] != '#' && key[t] != '(') {
      t --;
    }
    if (t < 0) {
      return -1;
    }
    if (key[t] == '#') {
      *extra_start = t;
      t ++;
      int flags = -1;
      *extra_end = parse_search_extra_common (key + t, key_len - t - 1, ')', limit, &flags) - key;
      if (flags != -1) {
        return flags;
      }
    }
    t = 0;
    while (t < key_len && key[t] != '(') {
      t ++;
    }
    if (t == key_len) {
      return -1;
    }
    int st = t;
    while (t >= 0 && key[t] != '#') {
      t --;
    }
    if (t < 0) {
      *extra_start = st;
      *extra_end = st;
      return 0;
    }
    *extra_start = t;
    t ++;
    int flags = -1;
    *extra_end = parse_search_extra_common (key + t, st - t, '(', limit, &flags) - key;
    if (flags != -1) {
      return flags;
    }
    return 0;
  } else {
    int t = key_len - 1;
    while (t >= 0 && key[t] != '#') {
      t --;
    }
    if (t < 0) {
      *extra_start = key_len;
      *extra_end = key_len;
      return 0;
    }
    *extra_start = t;
    t ++;
    *extra_end = parse_search_extra_common (key + t, key_len - t, 0, limit, &flags) - key;
    if (flags == -1) {
      flags = 0;
    }
    return flags;
  }
}