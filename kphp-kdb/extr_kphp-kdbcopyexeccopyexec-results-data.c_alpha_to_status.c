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
 int /*<<< orphan*/  status_to_alpha (int) ; 
 int /*<<< orphan*/  strcmp (char const* const,int /*<<< orphan*/ ) ; 

int alpha_to_status (const char *const status) {
  int i;
  for (i = 0; i < 16; i++) {
    if (!strcmp (status, status_to_alpha (i))) {
      return i;
    }
  }
  return -1;
}