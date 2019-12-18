#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int saved_r0; int saved_r2; int delay; int mode; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 int /*<<< orphan*/  CCP (int) ; 
 int /*<<< orphan*/  P1 ; 
 int /*<<< orphan*/  P2 ; 
 int RESET_WAIT ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int on26_read_regr (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  on26_write_regr (TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printk (char*,int,int) ; 
 int r0 () ; 
 int r1 () ; 
 int r2 () ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static int on26_test_port( PIA *pi)  /* hard reset */

{       int     i, m, d, x=0, y=0;

        pi->saved_r0 = r0();
        pi->saved_r2 = r2();

        d = pi->delay;
        m = pi->mode;
        pi->delay = 5;
        pi->mode = 0;

        w2(0xc);

        CCP(0x30); CCP(0); 

        w0(0xfe);w0(0xaa);w0(0x55);w0(0);w0(0xff);
        i = ((r1() & 0xf0) << 4); w0(0x87);
        i |= (r1() & 0xf0); w0(0x78);
        w0(0x20);w2(4);w2(5);
        i |= ((r1() & 0xf0) >> 4);
        w2(4);w0(0xff);

        if (i == 0xb5f) {

            w0(2); P1; w0(0);   P2;
            w0(3); P1; w0(0);   P2;
            w0(2); P1; w0(8);   P2; udelay(100);
            w0(2); P1; w0(0xa); P2; udelay(100);
            w0(2); P1; w0(8);   P2; udelay(1000);
            
            on26_write_regr(pi,0,6,0xa0);

            for (i=0;i<RESET_WAIT;i++) {
                on26_write_regr(pi,0,6,0xa0);
                x = on26_read_regr(pi,0,7);
                on26_write_regr(pi,0,6,0xb0);
                y = on26_read_regr(pi,0,7);
                if (!((x&0x80)||(y&0x80))) break;
                mdelay(100);
            }

	    if (i == RESET_WAIT) 
		printk("on26: Device reset failed (%x,%x)\n",x,y);

            w0(4); P1; w0(4); P1;
        }

        CCP(0x30);

        pi->delay = d;
        pi->mode = m;
        w0(pi->saved_r0);
        w2(pi->saved_r2);

        return 5;
}