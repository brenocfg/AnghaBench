#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
typedef  TYPE_1__** mixer_tab ;
struct TYPE_3__ {int regno; int polarity; int nbits; int bitoffs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static void
change_bits(mixer_tab *t, u_char *regval, int dev, int chn, int newval)
{
    	u_char mask;
    	int shift;

    	DEB(printf("ch_bits dev %d ch %d val %d old 0x%02x "
		"r %d p %d bit %d off %d\n",
		dev, chn, newval, *regval,
		(*t)[dev][chn].regno, (*t)[dev][chn].polarity,
		(*t)[dev][chn].nbits, (*t)[dev][chn].bitoffs ) );

    	if ( (*t)[dev][chn].polarity == 1)	/* reverse */
		newval = 100 - newval ;

    	mask = (1 << (*t)[dev][chn].nbits) - 1;
    	newval = (int) ((newval * mask) + 50) / 100; /* Scale it */
    	shift = (*t)[dev][chn].bitoffs /*- (*t)[dev][LEFT_CHN].nbits + 1*/;

    	*regval &= ~(mask << shift);        /* Filter out the previous value */
    	*regval |= (newval & mask) << shift;        /* Set the new value */
}