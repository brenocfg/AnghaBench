#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mode; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 char j44 (int,int) ; 
 int r0 () ; 
 int r1 () ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static void aten_read_block( PIA *pi, char * buf, int count )

{	int  k, a, b, c, d;

	switch (pi->mode) {

	case 0:	w0(0x48); w2(0xe); w2(6);
		for (k=0;k<count/2;k++) {
			w2(7); w2(6); w2(2);
			a = r1(); w0(0x58); b = r1();
			w2(0); d = r1(); w0(0x48); c = r1();
			buf[2*k] = j44(c,d);
			buf[2*k+1] = j44(a,b);
		}
		w2(0xc);
		break;

	case 1: w0(0x58); w2(0xe); w2(6);
		for (k=0;k<count/2;k++) {
			w2(0x27); w2(0x26); w2(0x22);
			a = r0(); w2(0x20); b = r0();
			buf[2*k] = b; buf[2*k+1] = a;
		}
		w2(0x26); w2(0xc);
		break;
	}
}