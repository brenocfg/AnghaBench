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
struct hard_trap_info {scalar_t__ tt; scalar_t__ signo; } ;

/* Variables and functions */
 int /*<<< orphan*/  exceptionHandler (scalar_t__,int /*<<< orphan*/ ) ; 
 struct hard_trap_info* hard_trap_info ; 
 int initialized ; 
 int /*<<< orphan*/  trap_low ; 

void
set_debug_traps (void)
{
  struct hard_trap_info *ht;

  for (ht = hard_trap_info; ht->tt && ht->signo; ht++)
    exceptionHandler(ht->tt, trap_low);

  initialized = 1;
}