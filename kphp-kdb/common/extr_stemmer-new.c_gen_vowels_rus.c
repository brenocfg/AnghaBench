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
 scalar_t__* _vowels_rus ; 
 size_t conv_rus_win1251 (scalar_t__) ; 
 int* vowels_rus ; 

void gen_vowels_rus (void) {
  int i;
  for (i = 0; _vowels_rus[i]; i++) {
    vowels_rus[conv_rus_win1251(_vowels_rus[i])] = 1;
  }
}