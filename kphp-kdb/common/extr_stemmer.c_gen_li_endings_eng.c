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
 scalar_t__* _li_endings_eng ; 
 size_t conv_eng (scalar_t__) ; 
 int* li_endings_eng ; 

void gen_li_endings_eng (void) {
  int i;
  for (i = 0; _li_endings_eng[i]; i++) {
    li_endings_eng[conv_eng(_li_endings_eng[i])] = 1;
  }
}