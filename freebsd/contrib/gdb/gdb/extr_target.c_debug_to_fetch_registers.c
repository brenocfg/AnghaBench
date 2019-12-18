#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* to_fetch_registers ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  debug_print_register (char*,int) ; 
 TYPE_1__ debug_target ; 
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static void
debug_to_fetch_registers (int regno)
{
  debug_target.to_fetch_registers (regno);
  debug_print_register ("target_fetch_registers", regno);
}