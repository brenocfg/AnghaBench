#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* bytecode_header_p; } ;
struct TYPE_3__ {int status_flags; } ;

/* Variables and functions */
 int CBC_CODE_FLAGS_STRICT_MODE ; 
 int /*<<< orphan*/  JERRY_ASSERT (int /*<<< orphan*/ ) ; 
 TYPE_2__* JERRY_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_top_context_p ; 

bool
vm_is_strict_mode (void)
{
  JERRY_ASSERT (JERRY_CONTEXT (vm_top_context_p) != NULL);

  return JERRY_CONTEXT (vm_top_context_p)->bytecode_header_p->status_flags & CBC_CODE_FLAGS_STRICT_MODE;
}