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
struct i387_fxsave {unsigned long fioff; unsigned long fooff; unsigned long mxcsr; unsigned long fop; int /*<<< orphan*/  foseg; int /*<<< orphan*/  fiseg; int /*<<< orphan*/  ftag; int /*<<< orphan*/  fstat; int /*<<< orphan*/  fctrl; int /*<<< orphan*/ * xmm_space; int /*<<< orphan*/ * st_space; } ;

/* Variables and functions */
 int /*<<< orphan*/  collect_register (int,char*) ; 
 int /*<<< orphan*/  collect_register_by_name (char*,unsigned long*) ; 
 int find_regno (char*) ; 
 int num_xmm_registers ; 

void
i387_cache_to_fxsave (void *buf)
{
  struct i387_fxsave *fp = (struct i387_fxsave *) buf;
  int i;
  int st0_regnum = find_regno ("st0");
  int xmm0_regnum = find_regno ("xmm0");
  unsigned long val, val2;

  for (i = 0; i < 8; i++)
    collect_register (i + st0_regnum, ((char *) &fp->st_space[0]) + i * 16);
  for (i = 0; i < num_xmm_registers; i++)
    collect_register (i + xmm0_regnum, ((char *) &fp->xmm_space[0]) + i * 16);

  collect_register_by_name ("fioff", &fp->fioff);
  collect_register_by_name ("fooff", &fp->fooff);
  collect_register_by_name ("mxcsr", &fp->mxcsr);
  
  /* This one's 11 bits... */
  collect_register_by_name ("fop", &val2);
  fp->fop = (val2 & 0x7FF) | (fp->fop & 0xF800);

  /* Some registers are 16-bit.  */
  collect_register_by_name ("fctrl", &val);
  *(unsigned short *) &fp->fctrl = val;

  collect_register_by_name ("fstat", &val);
  val &= 0xFFFF;
  *(unsigned short *) &fp->fstat = val;

  /* Convert to the simplifed tag form stored in fxsave data.  */
  collect_register_by_name ("ftag", &val);
  val &= 0xFFFF;
  for (i = 7; i >= 0; i--)
    {
      int tag = (val >> (i * 2)) & 3;

      if (tag != 3)
	val2 |= (1 << i);
    }
  *(unsigned short *) &fp->ftag = val2;

  collect_register_by_name ("fiseg", &val);
  val &= 0xFFFF;
  *(unsigned short *) &fp->fiseg = val;

  collect_register_by_name ("foseg", &val);
  val &= 0xFFFF;
  *(unsigned short *) &fp->foseg = val;
}