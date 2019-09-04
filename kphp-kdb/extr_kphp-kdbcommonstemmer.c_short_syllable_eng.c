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
 int /*<<< orphan*/ * syllable_exceptions_eng ; 
 scalar_t__* vowels_eng ; 

int short_syllable_eng (int *s, int n) {
  if (n >= 2 && vowels_eng[s[n - 2]]) {
     if ((n == 2 && !vowels_eng[s[n - 1]]) ||
                   (!vowels_eng[s[n - 3]] && !vowels_eng[s[n - 1]] && !syllable_exceptions_eng[s[n - 1]])) {
       return 1;
     }
  }
  return 0;
}