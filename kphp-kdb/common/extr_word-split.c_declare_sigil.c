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
 int* is_letter ; 
 int* is_letter_utf8 ; 

__attribute__((used)) static inline void declare_sigil (int c) {
  is_letter[c] |= 0x40;
  is_letter_utf8[c] |= 0x40;
}