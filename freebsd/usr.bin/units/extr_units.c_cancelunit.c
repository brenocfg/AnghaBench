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
struct unittype {char** denominator; char** numerator; } ;

/* Variables and functions */
 void* NULLUNIT ; 
 int strcmp (char*,char*) ; 

void 
cancelunit(struct unittype * theunit)
{
	char **den, **num;
	int comp;

	den = theunit->denominator;
	num = theunit->numerator;

	while (*num && *den) {
		comp = strcmp(*den, *num);
		if (!comp) {
/*      if (*den!=NULLUNIT) free(*den);
      if (*num!=NULLUNIT) free(*num);*/
			*den++ = NULLUNIT;
			*num++ = NULLUNIT;
		}
		else if (comp < 0)
			den++;
		else
			num++;
	}
}