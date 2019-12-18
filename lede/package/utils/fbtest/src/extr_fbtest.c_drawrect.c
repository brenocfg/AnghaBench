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
struct vidsize {int width; } ;
struct rect {int width; int y; int x; int height; TYPE_1__* col; } ;
struct pixelformat {int pixenum; int bpp; } ;
struct pixel {int* byte; } ;
struct TYPE_2__ {int r; } ;

/* Variables and functions */
#define  ARGB 132 
#define  ARGB1555 131 
#define  CLUT4 130 
#define  CLUT8 129 
#define  RGB565 128 
 int /*<<< orphan*/  col2pixel (struct pixel*,struct pixelformat const*,TYPE_1__*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int*,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

void drawrect(void *videoram, struct rect *r, const struct pixelformat *pixf, const struct vidsize *vids){
	int x,y,corwidth, bpp = 0, tocopy = 1;
	struct pixel pix;
	unsigned char *pmem = videoram;
	corwidth = r->width;	// actually only "corrected" for 4 Bit

	if (pixf->pixenum!=CLUT4&&pixf->pixenum!=CLUT8){
		switch (pixf->pixenum){
			case ARGB1555:
			case RGB565:
				bpp = 16;
				tocopy = 2;
				break;
			case ARGB:
				bpp = 32;
				tocopy = 4;
				break;
			default:
				printf ("drawrect: unknown pixelformat(%d) bpp:%d\n",pixf->pixenum,pixf->bpp);
				exit(1);
		}
		col2pixel(&pix,pixf,r->col);
	} else {
		switch (pixf->pixenum){	// CLUT = Colour LookUp Table (palette)
			case CLUT4:	// take red value as index in this case
				pix.byte[0]=(r->col->r)<<4|(r->col->r&0xf);	// slightly cryptic... "rect->colour->red"
				corwidth>>=1;	// we copy bytes
				bpp=4;
				tocopy=1;
				break;
			case CLUT8:
				pix.byte[0]=(r->col->r&0xff);
				bpp=8;
				tocopy=1;
				break;
		}
	}
	pmem=videoram+((((r->y*vids->width)+r->x)*bpp)>>3);
	for (y=0;y<r->height;y++){
		int offset = 0;
		for (x=0;x<corwidth;x++){
			memcpy (pmem+offset,pix.byte,tocopy);
			offset+=tocopy;
		}
		pmem +=((vids->width*bpp)>>3);	// skip one whole line, actually should be taken from "fix-info"
	}
}