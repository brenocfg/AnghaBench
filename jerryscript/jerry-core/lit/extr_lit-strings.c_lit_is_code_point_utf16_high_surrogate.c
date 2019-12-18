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
typedef  scalar_t__ lit_code_point_t ;

/* Variables and functions */
 scalar_t__ LIT_UTF16_HIGH_SURROGATE_MAX ; 
 scalar_t__ LIT_UTF16_HIGH_SURROGATE_MIN ; 

bool
lit_is_code_point_utf16_high_surrogate (lit_code_point_t code_point) /**< code point */
{
  return LIT_UTF16_HIGH_SURROGATE_MIN <= code_point && code_point <= LIT_UTF16_HIGH_SURROGATE_MAX;
}