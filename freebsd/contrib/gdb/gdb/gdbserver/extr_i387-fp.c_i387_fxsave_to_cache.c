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
struct i387_fxsave {unsigned long fioff; unsigned long fooff; unsigned long mxcsr; int fctrl; int fstat; int fiseg; int foseg; int fop; int /*<<< orphan*/ * xmm_space; int /*<<< orphan*/ * st_space; } ;

/* Variables and functions */
 int find_regno (char*) ; 
 int i387_ftag (struct i387_fxsave*,int) ; 
 int num_xmm_registers ; 
 int /*<<< orphan*/  supply_register (int,char*) ; 
 int /*<<< orphan*/  supply_register_by_name (char*,unsigned long*) ; 

void
i387_fxsave_to_cache (const void *buf)
{
  struct i387_fxsave *fp = (struct i387_fxsave *) buf;
  int i, top;
  int st0_regnum = find_regno ("st0");
  int xmm0_regnum = find_regno ("xmm0");
  unsigned long val;

  for (i = 0; i < 8; i++)
    supply_register (i + st0_regnum, ((char *) &fp->st_space[0]) + i * 16);
  for (i = 0; i < num_xmm_registers; i++)
    supply_register (i + xmm0_regnum, ((char *) &fp->xmm_space[0]) + i * 16);

  supply_register_by_name ("fioff", &fp->fioff);
  supply_register_by_name ("fooff", &fp->fooff);
  supply_register_by_name ("mxcsr", &fp->mxcsr);
  
  /* Some registers are 16-bit.  */
  val = fp->fctrl & 0xFFFF;
  supply_register_by_name ("fctrl", &val);

  val = fp->fstat & 0xFFFF;
  supply_register_by_name ("fstat", &val);

  /* Generate the form of ftag data that GDB expects.  */
  top = (fp->fstat >> 11) & 0x7;
  val = 0;
  for (i = 7; i >= 0; i--)
    {
      int tag;
      if (val & (1 << i))
	tag = i387_ftag (fp, (i + 8 - top) % 8);
      else
	tag = 3;
      val |= tag << (2 * i);
    }
  supply_register_by_name ("ftag", &val);

  val = fp->fiseg & 0xFFFF;
  supply_register_by_name ("fiseg", &val);

  val = fp->foseg & 0xFFFF;
  supply_register_by_name ("foseg", &val);

  val = (fp->fop) & 0x7FF;
  supply_register_by_name ("fop", &val);
}