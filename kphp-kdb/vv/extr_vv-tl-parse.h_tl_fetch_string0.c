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
 scalar_t__ tl_fetch_string_data (char*,int) ; 
 int tl_fetch_string_len (int) ; 

__attribute__((used)) static inline int tl_fetch_string0 (char *buf, int max_len) {
  int l = tl_fetch_string_len (max_len);
  if (l < 0) {
    return -1;
  }
  if (tl_fetch_string_data (buf, l) < 0) {
    return -1;
  }
  buf[l] = 0;
  return l;
}