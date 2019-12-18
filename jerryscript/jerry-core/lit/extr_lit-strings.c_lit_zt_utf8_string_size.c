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
typedef  int /*<<< orphan*/  lit_utf8_size_t ;
typedef  int /*<<< orphan*/  lit_utf8_byte_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

lit_utf8_size_t
lit_zt_utf8_string_size (const lit_utf8_byte_t *utf8_str_p) /**< zero-terminated utf-8 string */
{
  JERRY_ASSERT (utf8_str_p != NULL);
  return (lit_utf8_size_t) strlen ((const char *) utf8_str_p);
}