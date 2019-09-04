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

/* Variables and functions */
 int PPC_OPCODE_ANY ; 
 int PPC_OPCODE_POWER4 ; 

__attribute__((used)) static int
valid_bo (long value, int dialect, int extract)
{
  if ((dialect & PPC_OPCODE_POWER4) == 0)
    {
      int valid;
      /* Certain encodings have bits that are required to be zero.
	 These are (z must be zero, y may be anything):
	     001zy
	     011zy
	     1z00y
	     1z01y
	     1z1zz
      */
      switch (value & 0x14)
	{
	default:
	case 0:
	  valid = 1;
	  break;
	case 0x4:
	  valid = (value & 0x2) == 0;
	  break;
	case 0x10:
	  valid = (value & 0x8) == 0;
	  break;
	case 0x14:
	  valid = value == 0x14;
	  break;
	}
      /* When disassembling with -Many, accept power4 encodings too.  */
      if (valid
	  || (dialect & PPC_OPCODE_ANY) == 0
	  || !extract)
	return valid;
    }

  /* Certain encodings have bits that are required to be zero.
     These are (z must be zero, a & t may be anything):
	 0000z
	 0001z
	 0100z
	 0101z
	 001at
	 011at
	 1a00t
	 1a01t
	 1z1zz
  */
  if ((value & 0x14) == 0)
    return (value & 0x1) == 0;
  else if ((value & 0x14) == 0x14)
    return value == 0x14;
  else
    return 1;
}