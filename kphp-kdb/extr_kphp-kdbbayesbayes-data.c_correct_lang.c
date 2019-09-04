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

int correct_lang (int *v) {
  switch (*v) {
    case 'a':
      *v = 0x0430;
      return 1;
    case 'A':
      *v = 0x0410;
      return 1;
    case 'e':
      *v = 0x0435;
      return 1;
    case 'E':
      *v = 0x0415;
      return 1;
    case 'i':
      *v = 0x0418;
      return 1;
    case 'I':
      *v = 0x0438;
      return 1;
    default:
      return 0;
  }
}