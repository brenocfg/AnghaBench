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
 int /*<<< orphan*/ * l_case ; 
 int /*<<< orphan*/  lc_str_utf8 (char*,char const*,int) ; 
 scalar_t__ word_split_utf8 ; 

void lc_str (char *to, const char *from, int len) {
  if (word_split_utf8) {
    lc_str_utf8 (to, from, len);
    return;
  }
  while (len > 0) {
    *to++ = l_case[(unsigned char) *from++];
    len--;
  }
  *to = 0;
}