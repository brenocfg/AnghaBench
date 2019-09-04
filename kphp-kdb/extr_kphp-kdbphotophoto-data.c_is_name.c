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
 scalar_t__ MAX_NAME_LEN ; 
 int /*<<< orphan*/  is_letter (char) ; 
 scalar_t__ strlen (char*) ; 

int is_name (char *s) {
  if (s == NULL || *s == 0 || strlen (s) >= MAX_NAME_LEN) {
    return 0;
  }
  while (*s) {
    if (!is_letter (*s)) {
      return 0;
    }
    s++;
  }
  return 1;
}