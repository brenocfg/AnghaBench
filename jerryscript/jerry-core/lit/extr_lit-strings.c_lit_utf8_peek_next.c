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
typedef  int /*<<< orphan*/  lit_utf8_byte_t ;
typedef  int /*<<< orphan*/  ecma_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_ASSERT (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lit_read_code_unit_from_utf8 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

ecma_char_t
lit_utf8_peek_next (const lit_utf8_byte_t *buf_p) /**< [in,out] buffer with characters */
{
  JERRY_ASSERT (buf_p);
  ecma_char_t ch;

  lit_read_code_unit_from_utf8 (buf_p, &ch);

  return ch;
}