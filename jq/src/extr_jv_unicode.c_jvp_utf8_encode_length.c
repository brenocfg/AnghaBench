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

int jvp_utf8_encode_length(int codepoint) {
  if (codepoint <= 0x7F) return 1;
  else if (codepoint <= 0x7FF) return 2;
  else if (codepoint <= 0xFFFF) return 3;
  else return 4;
}