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
 unsigned int LittleLong (unsigned long) ; 
 long* ROQ_UB_tab ; 
 long* ROQ_UG_tab ; 
 long* ROQ_VG_tab ; 
 long* ROQ_VR_tab ; 
 scalar_t__* ROQ_YY_tab ; 

__attribute__((used)) static unsigned int yuv_to_rgb24( long y, long u, long v )
{ 
	long r,g,b,YY = (long)(ROQ_YY_tab[(y)]);

	r = (YY + ROQ_VR_tab[v]) >> 6;
	g = (YY + ROQ_UG_tab[u] + ROQ_VG_tab[v]) >> 6;
	b = (YY + ROQ_UB_tab[u]) >> 6;
	
	if (r<0) r = 0;
	if (g<0) g = 0;
	if (b<0) b = 0;
	if (r > 255) r = 255;
	if (g > 255) g = 255;
	if (b > 255) b = 255;
	
	return LittleLong ((unsigned long)((r)|(g<<8)|(b<<16))|(255UL<<24));
}