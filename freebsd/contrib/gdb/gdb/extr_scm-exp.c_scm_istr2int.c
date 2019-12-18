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
typedef  int LONGEST ;

/* Variables and functions */
 int SCM_BOOL_F ; 
 int SCM_MAKINUM (int) ; 

__attribute__((used)) static LONGEST
scm_istr2int (char *str, int len, int radix)
{
  int i = 0;
  LONGEST inum = 0;
  int c;
  int sign = 0;

  if (0 >= len)
    return SCM_BOOL_F;		/* zero scm_length */
  switch (str[0])
    {				/* leading sign */
    case '-':
    case '+':
      sign = str[0];
      if (++i == len)
	return SCM_BOOL_F;	/* bad if lone `+' or `-' */
    }
  do
    {
      switch (c = str[i++])
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	  c = c - '0';
	  goto accumulate;
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	  c = c - 'A' + 10;
	  goto accumulate;
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	  c = c - 'a' + 10;
	accumulate:
	  if (c >= radix)
	    return SCM_BOOL_F;	/* bad digit for radix */
	  inum *= radix;
	  inum += c;
	  break;
	default:
	  return SCM_BOOL_F;	/* not a digit */
	}
    }
  while (i < len);
  if (sign == '-')
    inum = -inum;
  return SCM_MAKINUM (inum);
}