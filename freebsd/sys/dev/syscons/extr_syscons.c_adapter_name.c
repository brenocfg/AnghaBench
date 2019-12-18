#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int va_type; int va_flags; } ;
typedef  TYPE_2__ video_adapter_t ;
struct TYPE_4__ {char* member_0; char* member_1; } ;

/* Variables and functions */
#define  KD_CGA 133 
#define  KD_EGA 132 
#define  KD_HERCULES 131 
#define  KD_MONO 130 
#define  KD_TGA 129 
#define  KD_VGA 128 
 int V_ADP_COLOR ; 

__attribute__((used)) static char
*adapter_name(video_adapter_t *adp)
{
    static struct {
	int type;
	char *name[2];
    } names[] = {
	{ KD_MONO,	{ "MDA",	"MDA" } },
	{ KD_HERCULES,	{ "Hercules",	"Hercules" } },
	{ KD_CGA,	{ "CGA",	"CGA" } },
	{ KD_EGA,	{ "EGA",	"EGA (mono)" } },
	{ KD_VGA,	{ "VGA",	"VGA (mono)" } },
	{ KD_TGA,	{ "TGA",	"TGA" } },
	{ -1,		{ "Unknown",	"Unknown" } },
    };
    int i;

    for (i = 0; names[i].type != -1; ++i)
	if (names[i].type == adp->va_type)
	    break;
    return names[i].name[(adp->va_flags & V_ADP_COLOR) ? 0 : 1];
}