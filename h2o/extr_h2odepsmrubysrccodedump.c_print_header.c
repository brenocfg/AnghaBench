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
typedef  scalar_t__ ptrdiff_t ;
typedef  int /*<<< orphan*/  mrb_irep ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ mrb_debug_get_line (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_header(mrb_irep *irep, ptrdiff_t i)
{
  int32_t line;

  line = mrb_debug_get_line(irep, i);
  if (line < 0) {
    printf("      ");
  }
  else {
    printf("%5d ", line);
  }

  printf("%03d ", (int)i);
}