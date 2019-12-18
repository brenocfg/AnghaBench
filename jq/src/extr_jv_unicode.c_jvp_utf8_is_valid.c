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
 char* jvp_utf8_next (char const*,char const*,int*) ; 

int jvp_utf8_is_valid(const char* in, const char* end) {
  int codepoint;
  while ((in = jvp_utf8_next(in, end, &codepoint))) {
    if (codepoint == -1) return 0;
  }
  return 1;
}