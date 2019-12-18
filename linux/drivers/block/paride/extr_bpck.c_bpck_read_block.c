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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int mode; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 int /*<<< orphan*/  WR (int,int) ; 
 char j44 (int,int) ; 
 char r0 () ; 
 int r1 () ; 
 char r4 () ; 
 int /*<<< orphan*/  r4l () ; 
 int /*<<< orphan*/  r4w () ; 
 int /*<<< orphan*/  t2 (int) ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static void bpck_read_block( PIA *pi, char * buf, int count )

{	int i, l, h;

	switch (pi->mode) {

      	case 0: WR(4,0x40);
		w0(0x40); t2(2);
		for (i=0;i<count;i++) {
		    t2(4); l = r1();
		    t2(4); h = r1();
		    buf[i] = j44(l,h);
		}
		WR(4,0);
		break;

	case 1: WR(4,0x50);
		w0(0x40); t2(2); t2(0x20);
      	        for(i=0;i<count;i++) { t2(4); buf[i] = r0(); }
	        t2(1); t2(0x20);
	        WR(4,0x10);
		break;

	case 2: WR(4,0x48);
		w0(0x40); w2(9); w2(0); w2(0x20);
		for (i=0;i<count;i++) buf[i] = r4();
		w2(0);
		WR(4,8);
		break;

        case 3: WR(4,0x48);
                w0(0x40); w2(9); w2(0); w2(0x20);
                for (i=0;i<count/2;i++) ((u16 *)buf)[i] = r4w();
                w2(0);
                WR(4,8);
                break;

        case 4: WR(4,0x48);
                w0(0x40); w2(9); w2(0); w2(0x20);
                for (i=0;i<count/4;i++) ((u32 *)buf)[i] = r4l();
                w2(0);
                WR(4,8);
                break;

	}
}