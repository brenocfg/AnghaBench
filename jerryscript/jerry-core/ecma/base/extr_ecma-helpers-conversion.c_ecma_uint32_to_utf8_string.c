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
typedef  int lit_utf8_size_t ;
typedef  scalar_t__ lit_utf8_byte_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 scalar_t__ JERRY_LIKELY (int) ; 
 scalar_t__ LIT_CHAR_0 ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,int) ; 

lit_utf8_size_t
ecma_uint32_to_utf8_string (uint32_t value, /**< value to convert */
                            lit_utf8_byte_t *out_buffer_p, /**< buffer for string */
                            lit_utf8_size_t buffer_size) /**< size of buffer */
{
  lit_utf8_byte_t *buf_p = out_buffer_p + buffer_size;

  do
  {
    JERRY_ASSERT (buf_p >= out_buffer_p);

    buf_p--;
    *buf_p = (lit_utf8_byte_t) ((value % 10) + LIT_CHAR_0);
    value /= 10;
  }
  while (value != 0);

  JERRY_ASSERT (buf_p >= out_buffer_p);

  lit_utf8_size_t bytes_copied = (lit_utf8_size_t) (out_buffer_p + buffer_size - buf_p);

  if (JERRY_LIKELY (buf_p != out_buffer_p))
  {
    memmove (out_buffer_p, buf_p, bytes_copied);
  }

  return bytes_copied;
}