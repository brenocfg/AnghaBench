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
 int /*<<< orphan*/  TL_ERROR_EXTRA_DATA ; 
 scalar_t__ TL_IN_REMAINING ; 
 int /*<<< orphan*/  tl_fetch_set_error_format (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static inline int tl_fetch_end (void) {
  if (TL_IN_REMAINING) {
    tl_fetch_set_error_format (TL_ERROR_EXTRA_DATA, "extra %d bytes after query", TL_IN_REMAINING);
    return -1;
  }
  return 1;
}