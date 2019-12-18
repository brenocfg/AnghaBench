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
typedef  scalar_t__ utf8_int32_t ;

/* Variables and functions */
 void* utf8codepoint (void const*,scalar_t__*) ; 
 scalar_t__ utf8lwrcodepoint (scalar_t__) ; 

int utf8casecmp(const void *src1, const void *src2) {
  utf8_int32_t src1_cp, src2_cp, src1_orig_cp, src2_orig_cp;

  for (;;) {
    src1 = utf8codepoint(src1, &src1_cp);
    src2 = utf8codepoint(src2, &src2_cp);

    // Take a copy of src1 & src2
    src1_orig_cp = src1_cp;
    src2_orig_cp = src2_cp;

    // Lower the srcs if required
    src1_cp = utf8lwrcodepoint(src1_cp);
    src2_cp = utf8lwrcodepoint(src2_cp);

    // Check if the lowered codepoints match
    if ((0 == src1_orig_cp) && (0 == src2_orig_cp)) {
      return 0;
    } else if (src1_cp == src2_cp) {
      continue;
    }

    // If they don't match, then we return which of the original's are less
    if (src1_orig_cp < src2_orig_cp) {
      return -1;
    } else if (src1_orig_cp > src2_orig_cp) {
      return 1;
    }
  }
}