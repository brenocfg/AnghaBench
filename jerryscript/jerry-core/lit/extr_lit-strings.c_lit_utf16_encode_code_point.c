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
typedef  int uint8_t ;
typedef  scalar_t__ lit_code_point_t ;
typedef  scalar_t__ ecma_char_t ;

/* Variables and functions */
 scalar_t__ LIT_UTF16_CODE_UNIT_MAX ; 
 scalar_t__ convert_code_point_to_high_surrogate (scalar_t__) ; 
 scalar_t__ convert_code_point_to_low_surrogate (scalar_t__) ; 

uint8_t
lit_utf16_encode_code_point (lit_code_point_t cp, /**< the code point we encode */
                             ecma_char_t *cu_p) /**< result of the encoding */
{
  if (cp <= LIT_UTF16_CODE_UNIT_MAX)
  {
    cu_p[0] = (ecma_char_t) cp;
    return 1;
  }

  cu_p[0] = convert_code_point_to_high_surrogate (cp);
  cu_p[1] = convert_code_point_to_low_surrogate (cp);
  return 2;
}