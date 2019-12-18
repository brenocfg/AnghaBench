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

/* Variables and functions */
 int /*<<< orphan*/  JERRY_FEATURE_ERROR_MESSAGES ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jerry_is_feature_enabled (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
str_to_uint (const char *num_str_p, /**< string to convert */
             char **out_p) /**< [out] end of the number */
{
  assert (jerry_is_feature_enabled (JERRY_FEATURE_ERROR_MESSAGES));

  uint32_t result = 0;

  while (*num_str_p >= '0' && *num_str_p <= '9')
  {
    result *= 10;
    result += (uint32_t) (*num_str_p - '0');
    num_str_p++;
  }

  if (out_p != NULL)
  {
    *out_p = num_str_p;
  }

  return result;
}