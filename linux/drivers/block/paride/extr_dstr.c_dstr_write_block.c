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
 int /*<<< orphan*/  P1 ; 
 int /*<<< orphan*/  P2 ; 
 int /*<<< orphan*/  P3 ; 
 int /*<<< orphan*/  w0 (char) ; 
 int /*<<< orphan*/  w2 (int) ; 
 int /*<<< orphan*/  w4 (char) ; 
 int /*<<< orphan*/  w4l (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w4w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dstr_write_block( PIA *pi, char * buf, int count )

{       int	k;

        w0(0x81); P1;
        if (pi->mode) { w0(0x19); } else { w0(9); }
        P2; w0(0x82); P1; P3; w0(0x20); P1;

        switch (pi->mode) {

        case 0:
        case 1: for (k=0;k<count;k++) {
                        w2(5); w0(buf[k]); w2(7);
                }
                w2(5); w2(4);
                break;

        case 2: w2(0xc5);
                for (k=0;k<count;k++) w4(buf[k]);
		w2(0xc4);
                break;

        case 3: w2(0xc5);
                for (k=0;k<count/2;k++) w4w(((u16 *)buf)[k]);
                w2(0xc4);
                break;

        case 4: w2(0xc5);
                for (k=0;k<count/4;k++) w4l(((u32 *)buf)[k]);
                w2(0xc4);
                break;

        }
}