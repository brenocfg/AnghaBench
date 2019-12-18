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
typedef  int /*<<< orphan*/  (* measure_fn ) () ;

/* Variables and functions */
 int /*<<< orphan*/  clear_stack () ; 
 int /*<<< orphan*/  emit (char*) ; 
 int /*<<< orphan*/  emit_uint32 (int) ; 
 int get_cycles () ; 
 int measure_stack () ; 
 int reset_cycles () ; 

__attribute__((used)) static void measure(measure_fn fn)
{
  clear_stack();
  uint32_t start_cycles = reset_cycles();
  fn();
  uint32_t end_cycles = get_cycles();
  uint32_t stack_words = measure_stack();

  emit("cycles = ");
  emit_uint32(end_cycles - start_cycles);
  emit("\n");
  emit("stack = ");
  emit_uint32(stack_words << 2);
  emit("\n");
}