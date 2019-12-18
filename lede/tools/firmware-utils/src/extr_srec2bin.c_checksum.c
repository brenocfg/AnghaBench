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
 int SRLerrorout (char*,char*) ; 
 scalar_t__ gh (char*,int) ; 
 int /*<<< orphan*/  isxdigit (int /*<<< orphan*/ ) ; 

int checksum(char *cp,int count)
{
  char *scp;
  int cksum;
  int dum;

  scp=cp;
  while(*scp)
  {
    if (!isxdigit(*scp++))
      return(SRLerrorout("Invalid hex digits",cp));
  }
  scp=cp;

  cksum=count;

  while(count)
  {
    cksum += gh(scp,2);
    if (count == 2)
        dum = ~cksum;
    scp += 2;
    count--;
  }
  cksum&=0x0ff; 
  //  printf("\nCk:%02x",cksum);
  return(cksum==0x0ff);
}