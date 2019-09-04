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
 scalar_t__* _double_eng ; 
 size_t conv_eng (scalar_t__) ; 
 int* double_eng ; 

void gen_double_eng (void) {
  int i;
  for (i = 0; _double_eng[i]; i++) {
    double_eng[conv_eng(_double_eng[i])] = 1;
  }
}