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
 int /*<<< orphan*/  st_printf (char*) ; 
 int verbosity ; 

void mt_test (void) {
  if (verbosity >= 2) {
    st_printf ("$3mt_test disabled$^ (should be compiled with -D\"ST_MEMTEST_ENABLED\")\n");
  }
}