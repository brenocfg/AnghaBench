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
struct s390_prologue_data {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  current_gdbarch ; 
 scalar_t__ s390_analyze_prologue (int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct s390_prologue_data*) ; 

__attribute__((used)) static CORE_ADDR
s390_skip_prologue (CORE_ADDR pc)
{
  struct s390_prologue_data data;
  CORE_ADDR skip_pc;
  skip_pc = s390_analyze_prologue (current_gdbarch, pc, (CORE_ADDR)-1, &data);
  return skip_pc ? skip_pc : pc;
}