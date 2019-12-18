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
typedef  int uint64_t ;

/* Variables and functions */
 char* cvmx_debug_hexchar ; 

__attribute__((used)) static void cvmx_debug_int64_to_strhex(char *str, uint64_t t)
{
  str[0] = cvmx_debug_hexchar[(t>>60)&0xF];
  str[1] = cvmx_debug_hexchar[(t>>56)&0xF];
  str[2] = cvmx_debug_hexchar[(t>>52)&0xF];
  str[3] = cvmx_debug_hexchar[(t>>48)&0xF];
  str[4] = cvmx_debug_hexchar[(t>>44)&0xF];
  str[5] = cvmx_debug_hexchar[(t>>40)&0xF];
  str[6] = cvmx_debug_hexchar[(t>>36)&0xF];
  str[7] = cvmx_debug_hexchar[(t>>32)&0xF];
  str[8] = cvmx_debug_hexchar[(t>>28)&0xF];
  str[9] = cvmx_debug_hexchar[(t>>24)&0xF];
  str[10] = cvmx_debug_hexchar[(t>>20)&0xF];
  str[11] = cvmx_debug_hexchar[(t>>16)&0xF];
  str[12] = cvmx_debug_hexchar[(t>>12)&0xF];
  str[13] = cvmx_debug_hexchar[(t>>8)&0xF];
  str[14] = cvmx_debug_hexchar[(t>>4)&0xF];
  str[15] = cvmx_debug_hexchar[(t>>0)&0xF];
  str[16] = 0;
}