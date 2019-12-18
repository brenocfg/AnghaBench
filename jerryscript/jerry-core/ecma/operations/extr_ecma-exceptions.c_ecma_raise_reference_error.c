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
typedef  int /*<<< orphan*/  ecma_value_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECMA_ERROR_REFERENCE ; 
 int /*<<< orphan*/  ecma_raise_standard_error (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

ecma_value_t
ecma_raise_reference_error (const char *msg_p) /**< error message */
{
  return ecma_raise_standard_error (ECMA_ERROR_REFERENCE, (const lit_utf8_byte_t *) msg_p);
}