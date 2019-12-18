#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_2__ {double value; scalar_t__ bits64; scalar_t__* bits32; } ;
typedef  TYPE_1__ double_bits_t ;

/* Variables and functions */
 scalar_t__ isnan (double) ; 
 int passed ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
check_double (const char *expr, double computed, double expected)
{
  double_bits_t computed_bits;
  double_bits_t expected_bits;

  computed_bits.value = computed;
  expected_bits.value = expected;

  printf ("%s = 0x%08x%08x [expected=0x%08x%08x] ", expr,
          (unsigned int) computed_bits.bits32[1], (unsigned int) computed_bits.bits32[0],
          (unsigned int) expected_bits.bits32[1], (unsigned int) expected_bits.bits32[0]);

  bool result;
  if (isnan (computed) && isnan (expected))
  {
    result = true;
  }
  else
  {
    int64_t diff = (int64_t) (computed_bits.bits64 - expected_bits.bits64);
    if (diff < 0)
    {
      diff = -diff;
    }

    if (diff <= 1) /* tolerate 1 bit of differene in the last place */
    {
      result = true;
      if (diff != 0)
      {
        printf ("APPROX ");
      }
    }
    else
    {
      result = false;
    }
  }
  printf ("%s\n", result ? "PASS" : "FAIL");

  passed &= result;
}