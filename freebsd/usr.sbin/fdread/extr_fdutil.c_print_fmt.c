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
struct fd_type {int secsize; int trans; int sectrac; int datalen; int gap; int tracks; int heads; int f_gap; int f_inter; int offset_side2; int flags; } ;

/* Variables and functions */
#define  FDC_1MBPS 131 
#define  FDC_250KBPS 130 
#define  FDC_300KBPS 129 
#define  FDC_500KBPS 128 
 int FL_2STEP ; 
 int FL_AUTO ; 
 int FL_MFM ; 
 int FL_PERPND ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

void
print_fmt(struct fd_type in)
{
	int secsize, speed;

	secsize = 128 << in.secsize;
	switch (in.trans) {
	case FDC_250KBPS:	speed = 250; break;
	case FDC_300KBPS:	speed = 300; break;
	case FDC_500KBPS:	speed = 500; break;
	case FDC_1MBPS:		speed = 1000; break;
	default:		speed = 1; break;
	}

	printf("%d,%d,%#x,%#x,%d,%d,%d,%#x,%d,%d",
	       in.sectrac, secsize, in.datalen, in.gap, in.tracks,
	       speed, in.heads, in.f_gap, in.f_inter, in.offset_side2);
	if (in.flags & FL_MFM)
		printf(",+mfm");
	if (in.flags & FL_2STEP)
		printf(",+2step");
	if (in.flags & FL_PERPND)
		printf(",+perpnd");
	if (in.flags & FL_AUTO)
		printf(",+auto");
	putc('\n', stdout);
}