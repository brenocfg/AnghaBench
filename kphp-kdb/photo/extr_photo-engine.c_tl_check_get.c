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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  index_mode ; 
 int /*<<< orphan*/  tl_fetch_set_error_format (int,char*) ; 
 scalar_t__ write_only ; 

void tl_check_get (void) {
  assert (!index_mode);
  if (write_only) {
    tl_fetch_set_error_format (-4001, "Get operations are unsupported in write_only mode");
  }
}