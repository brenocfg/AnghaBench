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
typedef  int /*<<< orphan*/  ecma_value_t ;

/* Variables and functions */
 int ECMA_STATUS_EXCEPTION ; 
 int JERRY_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_create_error_reference (int,int) ; 
 int /*<<< orphan*/  error_value ; 
 int /*<<< orphan*/  status_flags ; 

ecma_value_t
ecma_create_error_reference_from_context (void)
{
  return ecma_create_error_reference (JERRY_CONTEXT (error_value),
                                      (JERRY_CONTEXT (status_flags) & ECMA_STATUS_EXCEPTION) != 0);
}