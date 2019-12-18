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
struct pixelformat {int pixenum; } ;
struct pixel {int* byte; } ;
struct colour {int r; int g; int b; int a; } ;

/* Variables and functions */
#define  ARGB 130 
#define  ARGB1555 129 
#define  RGB565 128 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*) ; 

void col2pixel (struct pixel *pix, const struct pixelformat *pixf, const struct colour *col){
	switch (pixf->pixenum){
		case RGB565:
			pix->byte[0]=(col->r&0xf8)|(col->g&0xfc)>>5;
			pix->byte[1]=(col->g&0xfc)<<3|(col->b&0xf8)>>3;
			break;
		case ARGB1555:
			pix->byte[0]=(col->a&0x80)|(col->r&0xf8)>>1|(col->g&0xf8)>>6;
			pix->byte[1]=(col->g&0xf8)<<2|(col->b&0xf8)>>3;
			break;
		case ARGB:
			pix->byte[0]=col->a;
			pix->byte[1]=col->r;
			pix->byte[2]=col->g;
			pix->byte[3]=col->b;
			break;
		default:
			printf ("unknown pixelformat\n");
			exit(1);
	}
}