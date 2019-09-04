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
 long* ROQ_UB_tab ; 
 long* ROQ_UG_tab ; 
 long* ROQ_VG_tab ; 
 long* ROQ_VR_tab ; 
 scalar_t__* ROQ_YY_tab ; 

__attribute__((used)) static unsigned short yuv_to_rgb( long y, long u, long v )
{ 
	long r,g,b,YY = (long)(ROQ_YY_tab[(y)]);

	r = (YY + ROQ_VR_tab[v]) >> 9;
	g = (YY + ROQ_UG_tab[u] + ROQ_VG_tab[v]) >> 8;
	b = (YY + ROQ_UB_tab[u]) >> 9;
	
	if (r<0) r = 0;
	if (g<0) g = 0;
	if (b<0) b = 0;
	if (r > 31) r = 31;
	if (g > 63) g = 63;
	if (b > 31) b = 31;

	return (unsigned short)((r<<11)+(g<<5)+(b));
}