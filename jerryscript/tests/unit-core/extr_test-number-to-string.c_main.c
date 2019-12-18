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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  str ;
typedef  int /*<<< orphan*/  nums ;
typedef  int /*<<< orphan*/  lit_utf8_size_t ;
typedef  int /*<<< orphan*/  lit_utf8_byte_t ;
typedef  int /*<<< orphan*/  const ecma_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  INFINITY ; 
 int /*<<< orphan*/  NAN ; 
 int /*<<< orphan*/  TEST_INIT () ; 
 int /*<<< orphan*/  ecma_number_to_utf8_string (int /*<<< orphan*/  const,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 

int
main (void)
{
  TEST_INIT ();

  const lit_utf8_byte_t *strings[] =
  {
    (const lit_utf8_byte_t *) "1",
    (const lit_utf8_byte_t *) "0.5",
    (const lit_utf8_byte_t *) "12345",
    (const lit_utf8_byte_t *) "12345.123",
    (const lit_utf8_byte_t *) "1e-45",
    (const lit_utf8_byte_t *) "-2.5e+38",
    (const lit_utf8_byte_t *) "NaN",
    (const lit_utf8_byte_t *) "Infinity",
    (const lit_utf8_byte_t *) "-Infinity",
    (const lit_utf8_byte_t *) "0",
    (const lit_utf8_byte_t *) "0",
  };

  const ecma_number_t nums[] =
  {
    (ecma_number_t) 1.0,
    (ecma_number_t) 0.5,
    (ecma_number_t) 12345.0,
    (ecma_number_t) 12345.123,
    (ecma_number_t) 1.0e-45,
    (ecma_number_t) -2.5e+38,
    (ecma_number_t) NAN,
    (ecma_number_t) INFINITY,
    (ecma_number_t) -INFINITY,
    (ecma_number_t) +0.0,
    (ecma_number_t) -0.0
  };

  for (uint32_t i = 0;
       i < sizeof (nums) / sizeof (nums[0]);
       i++)
  {
    lit_utf8_byte_t str[64];

    lit_utf8_size_t str_size = ecma_number_to_utf8_string (nums[i], str, sizeof (str));

    if (strncmp ((char *) str, (char *) strings[i], str_size) != 0)
    {
      return 1;
    }
  }

  return 0;
}