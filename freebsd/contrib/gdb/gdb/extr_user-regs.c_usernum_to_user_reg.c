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
struct user_reg {struct user_reg* next; } ;
struct gdbarch {int dummy; } ;
struct gdb_user_regs {struct user_reg* first; } ;

/* Variables and functions */
 struct gdb_user_regs* gdbarch_data (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_regs_data ; 

__attribute__((used)) static struct user_reg *
usernum_to_user_reg (struct gdbarch *gdbarch, int usernum)
{
  struct gdb_user_regs *regs = gdbarch_data (gdbarch, user_regs_data);
  struct user_reg *reg;
  for (reg = regs->first; reg != NULL; reg = reg->next)
    {
      if (usernum == 0)
	return reg;
      usernum--;
    }
  return NULL;
}