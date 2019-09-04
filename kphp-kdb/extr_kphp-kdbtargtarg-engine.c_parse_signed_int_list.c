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
 int MAX_USERS ; 
 long* R ; 
 long strtol (char*,char**,int) ; 

int parse_signed_int_list (char *text, int text_len) {
  int i = 0;
  long x;
  char *ptr = text, *ptr_e = text + text_len, *ptr_n;
  while (ptr < ptr_e) {
    if (i && *ptr++ != ',') {
      return -1;
    }
    R[i++] = x = strtol (ptr, &ptr_n, 10);
    if (ptr == ptr_n || i == MAX_USERS || x <= -0x7fffffff || x >= 0x7fffffff) {
      return -1;
    }
    ptr = ptr_n;
  }
  return i;
}