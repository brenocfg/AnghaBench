#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ byte ;
struct TYPE_2__ {int numclusters; } ;

/* Variables and functions */
 TYPE_1__* dvis ; 

int Q2_CompressVis (byte *vis, byte *dest)
{
	int		j;
	int		rep;
	int		visrow;
	byte	*dest_p;
	
	dest_p = dest;
//	visrow = (r_numvisleafs + 7)>>3;
	visrow = (dvis->numclusters + 7)>>3;
	
	for (j=0 ; j<visrow ; j++)
	{
		*dest_p++ = vis[j];
		if (vis[j])
			continue;

		rep = 1;
		for ( j++; j<visrow ; j++)
			if (vis[j] || rep == 255)
				break;
			else
				rep++;
		*dest_p++ = rep;
		j--;
	}
	
	return dest_p - dest;
}