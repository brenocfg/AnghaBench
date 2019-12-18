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
typedef  scalar_t__ u_int8_t ;

/* Variables and functions */
#define  V_INFO_MM_CGA 139 
#define  V_INFO_MM_DIRECT 138 
#define  V_INFO_MM_HGC 137 
 int V_INFO_MM_OTHER ; 
#define  V_INFO_MM_PACKED 136 
#define  V_INFO_MM_PLANAR 135 
#define  V_INFO_MM_TEXT 134 
#define  V_MMCGA 133 
#define  V_MMDIRCOLOR 132 
#define  V_MMEGA 131 
#define  V_MMHGC 130 
#define  V_MMPACKED 129 
#define  V_MMTEXT 128 

__attribute__((used)) static int
vesa_translate_mmodel(u_int8_t vmodel)
{
	static struct {
		u_int8_t vmodel;
		int mmodel;
	} mtable[] = {
		{ V_MMTEXT,	V_INFO_MM_TEXT },
		{ V_MMCGA,	V_INFO_MM_CGA },
		{ V_MMHGC,	V_INFO_MM_HGC },
		{ V_MMEGA,	V_INFO_MM_PLANAR },
		{ V_MMPACKED,	V_INFO_MM_PACKED },
		{ V_MMDIRCOLOR,	V_INFO_MM_DIRECT },
	};
	int i;

	for (i = 0; mtable[i].mmodel >= 0; ++i) {
		if (mtable[i].vmodel == vmodel)
			return (mtable[i].mmodel);
	}
	return (V_INFO_MM_OTHER);
}