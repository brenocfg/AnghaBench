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
struct user_reg {char const* name; struct user_reg* next; } ;
struct gdbarch {int dummy; } ;
struct gdb_user_regs {struct user_reg* first; } ;

/* Variables and functions */
 int NUM_PSEUDO_REGS ; 
 int NUM_REGS ; 
 struct gdb_user_regs* gdbarch_data (struct gdbarch*,int /*<<< orphan*/ ) ; 
 int gdbarch_num_pseudo_regs (struct gdbarch*) ; 
 int gdbarch_num_regs (struct gdbarch*) ; 
 char* gdbarch_register_name (struct gdbarch*,int) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  user_regs_data ; 

int
user_reg_map_name_to_regnum (struct gdbarch *gdbarch, const char *name,
			     int len)
{
  /* Make life easy, set the len to something reasonable.  */
  if (len < 0)
    len = strlen (name);

  /* Search register name space first - always let an architecture
     specific register override the user registers.  */
  {
    int i;
    int maxregs = (gdbarch_num_regs (gdbarch)
		   + gdbarch_num_pseudo_regs (gdbarch));
    for (i = 0; i < maxregs; i++)
      {
	const char *regname = gdbarch_register_name (gdbarch, i);
	if (regname != NULL && len == strlen (regname)
	    && strncmp (regname, name, len) == 0)
	  {
	    return i;
	  }
      }
  }

  /* Search the user name space.  */
  {
    struct gdb_user_regs *regs = gdbarch_data (gdbarch, user_regs_data);
    struct user_reg *reg;
    int nr;
    for (nr = 0, reg = regs->first; reg != NULL; reg = reg->next, nr++)
      {
	if ((len < 0 && strcmp (reg->name, name))
	    || (len == strlen (reg->name)
		&& strncmp (reg->name, name, len) == 0))
	  return NUM_REGS + NUM_PSEUDO_REGS + nr;
      }
  }

  return -1;
}