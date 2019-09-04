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

int base64_to_base64url (const char *const input, char *output, int olen) {
  int i = 0;
  while (input[i] && i < olen) {
    if (input[i] == '+') {
      output[i] = '-';
    } else if (input[i] == '/') {
      output[i] = '_';
    } else if (input[i] != '=') {
      output[i] = input[i];
    } else {
      break;
    }
    i++;
  }
  if (i >= olen) {
    return -1;
  }
  output[i] = 0;
  return 0;
}