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
 char* rBuff ; 
 int rBuff_len ; 
 char* rptr ; 

int readin_reset (char *data, int data_len) {
  rBuff = data;
  rBuff_len = data_len;
  rptr = rBuff;
  return 0;
}