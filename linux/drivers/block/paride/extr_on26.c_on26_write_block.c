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
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 
 int /*<<< orphan*/  w3 (int) ; 
 int /*<<< orphan*/  w4 (int) ; 
 int /*<<< orphan*/  w4l (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w4w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on26_write_block( PIA *pi, char * buf, int count )

{       int	k;

        switch (pi->mode) {

        case 0: 
        case 1: w0(1); P1; w0(1); P2; 
		w0(2); P1; w0(0x18+pi->mode); P2; w0(0); P1;
		udelay(10);
		for (k=0;k<count/2;k++) {
                        w2(5); w0(buf[2*k]); 
			w2(7); w0(buf[2*k+1]);
                }
                w2(5); w2(4);
		w0(2); P1; w0(8+pi->mode); P2;
                break;

        case 2: w3(1); w3(1); w2(5); w4(1); w2(4);
		w3(0); w3(0); w2(0xc5);
		udelay(10);
                for (k=0;k<count;k++) w4(buf[k]);
		w2(0xc4);
                break;

        case 3: w3(1); w3(1); w2(5); w4(1); w2(4);
                w3(0); w3(0); w2(0xc5);
                udelay(10);
                for (k=0;k<count/2;k++) w4w(((u16 *)buf)[k]);
                w2(0xc4);
                break;

        case 4: w3(1); w3(1); w2(5); w4(1); w2(4);
                w3(0); w3(0); w2(0xc5);
                udelay(10);
                for (k=0;k<count/4;k++) w4l(((u32 *)buf)[k]);
                w2(0xc4);
                break;

        }

}