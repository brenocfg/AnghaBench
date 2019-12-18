#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_4__ {int* index; } ;
typedef  TYPE_1__ BMP_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  bmp_SetPix (TYPE_1__*,int,int,int) ; 

__attribute__((used)) static void
bmp_DecodeRLE4(BMP_INFO *info, int line)
{
    int		count;		/* run count */
    u_char	val;
    int		x,y;		/* screen position */
    
    x = 0;			/* starting position */
    y = line;
    
    /* loop reading data */
    for (;;) {
	/*
	 * encoded mode starts with a run length, and then a byte with
	 * two colour indexes to alternate between for the run
	 */
	if (*info->index) {
	    for (count = 0; count < *info->index; count++, x++) {
		if (count & 1) {		/* odd count, low nybble */
		    bmp_SetPix(info, x, y, *(info->index+1) & 0x0f);
		} else {			/* even count, high nybble */
		    bmp_SetPix(info, x, y, (*(info->index+1) >>4) & 0x0f);
		}
	    }
	    info->index += 2;
        /* 
	 * A leading zero is an escape; it may signal the end of the 
	 * bitmap, a cursor move, or some absolute data.
	 */
	} else {	/* zero tag may be absolute mode or an escape */
	    switch (*(info->index+1)) {
	    case 0:				/* end of line */
		info->index += 2;
		return;
	    case 1:				/* end of bitmap */
		info->index = NULL;
		return;
	    case 2:				/* move */
		x += *(info->index + 2);	/* new coords */
		y += *(info->index + 3);
		info->index += 4;
		break;
	    default:				/* literal bitmap data */
		for (count = 0; count < *(info->index + 1); count++, x++) {
		    val = *(info->index + 2 + (count / 2));	/* byte with nybbles */
		    if (count & 1) {
			val &= 0xf;		/* get low nybble */
		    } else {
			val = (val >> 4);	/* get high nybble */
		    }
		    bmp_SetPix(info, x, y, val);
		}
		/* warning, this depends on integer truncation, do not hand-optimise! */
		info->index += 2 + ((count + 3) / 4) * 2;
		break;
	    }
	}
    }
}