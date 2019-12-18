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
typedef  int /*<<< orphan*/  l ;
typedef  int ULONGEST ;

/* Variables and functions */
 char* get_cell () ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned short,...) ; 
 int thirty_two ; 

char *
phex_nz (ULONGEST l, int sizeof_l)
{
  char *str;
  switch (sizeof_l)
    {
    case 8:
      {
	unsigned long high = (unsigned long) (l >> thirty_two);
	str = get_cell ();
	if (high == 0)
	  sprintf (str, "%lx", (unsigned long) (l & 0xffffffff));
	else
	  sprintf (str, "%lx%08lx", high, (unsigned long) (l & 0xffffffff));
	break;
      }
    case 4:
      str = get_cell ();
      sprintf (str, "%lx", (unsigned long) l);
      break;
    case 2:
      str = get_cell ();
      sprintf (str, "%x", (unsigned short) (l & 0xffff));
      break;
    default:
      str = phex_nz (l, sizeof (l));
      break;
    }
  return str;
}