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
struct TYPE_3__ {int mode; int /*<<< orphan*/  saved_r2; int /*<<< orphan*/  saved_r0; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 int /*<<< orphan*/  WR (int,int) ; 
 int /*<<< orphan*/  r0 () ; 
 int /*<<< orphan*/  r2 () ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static void epia_connect ( PIA *pi  )

{       pi->saved_r0 = r0();
        pi->saved_r2 = r2();

        w2(4); w0(0xa0); w0(0x50); w0(0xc0); w0(0x30); w0(0xa0); w0(0);
        w2(1); w2(4);
        if (pi->mode >= 3) { 
                w0(0xa); w2(1); w2(4); w0(0x82); w2(4); w2(0xc); w2(4);
                w2(0x24); w2(0x26); w2(4);
        }
        WR(0x86,8);  
}