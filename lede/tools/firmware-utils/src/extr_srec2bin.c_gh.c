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
typedef  int bit32u ;

/* Variables and functions */
 int /*<<< orphan*/  SRLerrorout (char*,char*) ; 

bit32u gh(char *cp,int nibs)
{
  int i;
  bit32u j;

  j=0;

  for(i=0;i<nibs;i++)
  {
    j<<=4;
    if ((*cp>='a')&&(*cp<='z')) *cp &= 0x5f;
    if ((*cp>='0')&&(*cp<='9')) 
      j += (*cp-0x30);
     else
      if ((*cp>='A')&&(*cp<='F'))
        j += (*cp-0x37);
       else
        SRLerrorout("Bad Hex char", cp);
    cp++;
  }
  return(j);
}