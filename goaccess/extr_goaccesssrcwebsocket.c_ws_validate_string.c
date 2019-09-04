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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (char*) ; 
 scalar_t__ UTF8_INVAL ; 
 scalar_t__ UTF8_VALID ; 
 scalar_t__ verify_utf8 (scalar_t__*,char const*,int) ; 

int
ws_validate_string (const char *str, int len)
{
  uint32_t state = UTF8_VALID;

  if (verify_utf8 (&state, str, len) == UTF8_INVAL) {
    LOG (("Invalid UTF8 data!\n"));
    return 1;
  }
  if (state != UTF8_VALID) {
    LOG (("Invalid UTF8 data!\n"));
    return 1;
  }

  return 0;
}