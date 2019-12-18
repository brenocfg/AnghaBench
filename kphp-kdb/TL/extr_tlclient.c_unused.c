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
 int /*<<< orphan*/  compiler ; 
 scalar_t__ log_file ; 
 scalar_t__ stdout ; 
 int tl_schema_print_unused_types (int /*<<< orphan*/ *,scalar_t__) ; 

int unused (char *s) {
  int r = tl_schema_print_unused_types (&compiler, stdout);
  if (log_file) {
    tl_schema_print_unused_types (&compiler, log_file);
  }
  return r;
}