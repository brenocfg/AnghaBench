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
typedef  int UBYTE ;

/* Variables and functions */
 int BLACK ; 
 int DKGREY ; 
 int LTGREY ; 
 int /*<<< orphan*/  M_FILL ; 
 int /*<<< orphan*/  M_NOFILL ; 
 int /*<<< orphan*/  SOLID ; 
 int WHITE ; 
 int /*<<< orphan*/  XOR ; 
 int /*<<< orphan*/  box (int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  circle (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  color (int,int,int /*<<< orphan*/ ) ; 
 int getpix (int,int) ; 
 int /*<<< orphan*/  gotogxy (int,int) ; 
 int /*<<< orphan*/  gprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  plot_point (int,int) ; 

void main(void)
{
    UBYTE  a,b,c,d,e;
    c=0;
    /* Draw many characters on the screen with different fg and bg colours */
    for (a=0; a<=15; a++) {
	for (b=0; b<=15; b++) {
	    gotogxy(b,a);
	    d=a/4;
	    e=b/4;
	    if (d==e) {
		d=3-e;
	    }
	    color(d,e,SOLID);
	    gprintf("%c",c++);
	} 
    }

    /* Draw two circles, a line, and two boxes in different drawing modes */
    color(LTGREY,WHITE,SOLID);
    circle(140,20,15,M_FILL);
    color(BLACK,WHITE,SOLID);
    circle(140,20,10,M_NOFILL);
    color(DKGREY,WHITE,XOR);
    circle(120,40,30,M_FILL);
    line(0,0,159,143);
    color(BLACK,LTGREY,SOLID);
    box(0,130,40,143,M_NOFILL);
    box(50,130,90,143,M_FILL);

    /* Scroll the screen using the hardest method imaginable :) */
    for (c=0; c<=143; c++) {
	for (b=0; b<=142; b++) {
	    for (a=0; a<=159; a++) {
		color(getpix(a,b+1),WHITE,SOLID);
		plot_point(a,b);
	    }
	    color(WHITE,WHITE,SOLID);
	}
	line(0,143,159,143);
    }
}