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
struct i387_fxsave {unsigned char* st_space; } ;

/* Variables and functions */

__attribute__((used)) static int
i387_ftag (struct i387_fxsave *fp, int regno)
{
  unsigned char *raw = &fp->st_space[regno * 16];
  unsigned int exponent;
  unsigned long fraction[2];
  int integer;

  integer = raw[7] & 0x80;
  exponent = (((raw[9] & 0x7f) << 8) | raw[8]);
  fraction[0] = ((raw[3] << 24) | (raw[2] << 16) | (raw[1] << 8) | raw[0]);
  fraction[1] = (((raw[7] & 0x7f) << 24) | (raw[6] << 16)
                 | (raw[5] << 8) | raw[4]);

  if (exponent == 0x7fff)
    {
      /* Special.  */
      return (2);
    }
  else if (exponent == 0x0000)
    {
      if (fraction[0] == 0x0000 && fraction[1] == 0x0000 && !integer)
        {
          /* Zero.  */
          return (1);
        }
      else
        {
          /* Special.  */
          return (2);
        }
    }
  else
    {
      if (integer)
        {
          /* Valid.  */
          return (0);
        }
      else
        {
          /* Special.  */
          return (2);
        }
    }
}