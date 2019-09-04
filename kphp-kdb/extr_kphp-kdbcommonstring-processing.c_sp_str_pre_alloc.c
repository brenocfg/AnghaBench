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
 scalar_t__ STRING_PROCESS_BUF_SIZE ; 
 int sp_errno ; 
 char* str_buf ; 
 scalar_t__ str_buf_n ; 

char *sp_str_pre_alloc (int len) {
//  we don't need to reset error level on each call
//  we check error level only once after all allocations have done
//  sp_errno = 0; // reset error level
  if (str_buf_n + len + 1 > STRING_PROCESS_BUF_SIZE) {
    sp_errno = 2;
    return NULL;
  }

  return str_buf + str_buf_n;
}