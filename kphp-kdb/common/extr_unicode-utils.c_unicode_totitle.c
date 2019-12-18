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
 int unicode_toupper (int) ; 

int unicode_totitle (int code) {
  if ((unsigned int)(code - 0x1c4) < 9u ||
      (unsigned int)(code - 0x1f1) < 3u) {
    return ((code * 685) >> 11) * 3;
  }

  return unicode_toupper (code);
}