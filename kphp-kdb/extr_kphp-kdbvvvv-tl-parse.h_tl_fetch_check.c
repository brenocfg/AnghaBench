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
 scalar_t__ TL_ERROR ; 
 int /*<<< orphan*/  TL_ERROR_INTERNAL ; 
 int /*<<< orphan*/  TL_ERROR_SYNTAX ; 
 int TL_IN_POS ; 
 int TL_IN_REMAINING ; 
 int /*<<< orphan*/  TL_IN_TYPE ; 
 int /*<<< orphan*/  tl_fetch_set_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_fetch_set_error_format (int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static inline int tl_fetch_check (int nbytes) {
  if (!TL_IN_TYPE) {
    tl_fetch_set_error ("Trying to read from unitialized in buffer", TL_ERROR_INTERNAL);
    return -1;
  }
  if (nbytes >= 0) {
    if (TL_IN_REMAINING < nbytes) {
      tl_fetch_set_error_format (TL_ERROR_SYNTAX, "Trying to read %d bytes at position %d (size = %d)", nbytes, TL_IN_POS, TL_IN_POS + TL_IN_REMAINING);
      return -1;
    }
  } else {
    if (TL_IN_POS < -nbytes) {
      tl_fetch_set_error_format (TL_ERROR_SYNTAX, "Trying to read %d bytes at position %d (size = %d)", nbytes, TL_IN_POS, TL_IN_POS + TL_IN_REMAINING);
      return -1;
    }
  }
  if (TL_ERROR) {
    return -1;
  }
  return 0;
}