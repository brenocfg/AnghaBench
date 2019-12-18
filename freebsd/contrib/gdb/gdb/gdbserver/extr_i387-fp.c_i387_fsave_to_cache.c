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
struct i387_fsave {unsigned long fioff; unsigned long fooff; int fctrl; int fstat; int ftag; int fiseg; int foseg; int fop; int /*<<< orphan*/ * st_space; } ;

/* Variables and functions */
 int find_regno (char*) ; 
 int /*<<< orphan*/  supply_register (int,char*) ; 
 int /*<<< orphan*/  supply_register_by_name (char*,unsigned long*) ; 

void
i387_fsave_to_cache (const void *buf)
{
  struct i387_fsave *fp = (struct i387_fsave *) buf;
  int i;
  int st0_regnum = find_regno ("st0");
  unsigned long val;

  for (i = 0; i < 8; i++)
    supply_register (i + st0_regnum, ((char *) &fp->st_space[0]) + i * 10);

  supply_register_by_name ("fioff", &fp->fioff);
  supply_register_by_name ("fooff", &fp->fooff);
  
  /* Some registers are 16-bit.  */
  val = fp->fctrl & 0xFFFF;
  supply_register_by_name ("fctrl", &val);

  val = fp->fstat & 0xFFFF;
  supply_register_by_name ("fstat", &val);

  val = fp->ftag & 0xFFFF;
  supply_register_by_name ("ftag", &val);

  val = fp->fiseg & 0xFFFF;
  supply_register_by_name ("fiseg", &val);

  val = fp->foseg & 0xFFFF;
  supply_register_by_name ("foseg", &val);

  val = (fp->fop) & 0x7FF;
  supply_register_by_name ("fop", &val);
}