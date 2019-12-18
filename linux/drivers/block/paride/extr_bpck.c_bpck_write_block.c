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
 int /*<<< orphan*/  t2 (int) ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 
 int /*<<< orphan*/  w4 (char) ; 
 int /*<<< orphan*/  w4l (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w4w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bpck_write_block( PIA *pi, char * buf, int count )

{	int i;

	switch (pi->mode) {

	case 0: WR(4,0x40);
		w0(0x40); t2(2); t2(1);
		for (i=0;i<count;i++) { w0(buf[i]); t2(4); }
		WR(4,0);
		break;

	case 1: WR(4,0x50);
                w0(0x40); t2(2); t2(1);
                for (i=0;i<count;i++) { w0(buf[i]); t2(4); }
                WR(4,0x10);
		break;

	case 2: WR(4,0x48);
		w0(0x40); w2(9); w2(0); w2(1);
		for (i=0;i<count;i++) w4(buf[i]);
		w2(0);
		WR(4,8);
		break;

        case 3: WR(4,0x48);
                w0(0x40); w2(9); w2(0); w2(1);
                for (i=0;i<count/2;i++) w4w(((u16 *)buf)[i]);
                w2(0);
                WR(4,8);
                break;
 
        case 4: WR(4,0x48);
                w0(0x40); w2(9); w2(0); w2(1);
                for (i=0;i<count/4;i++) w4l(((u32 *)buf)[i]);
                w2(0);
                WR(4,8);
                break;
 	}
}