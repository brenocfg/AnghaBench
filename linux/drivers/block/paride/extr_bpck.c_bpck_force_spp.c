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
struct TYPE_3__ {int saved_r0; int unit; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 int r0 () ; 
 int /*<<< orphan*/  t2 (int) ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static void bpck_force_spp ( PIA *pi )

/* This fakes the EPP protocol to turn off EPP ... */

{       pi->saved_r0 = r0();
        w0(0xff-pi->unit); w2(4); w0(pi->unit);
        t2(8); t2(8); t2(8); 
        t2(2); t2(2);

        w2(0); 
        w0(4); w2(9); w2(0); 
        w0(0); w2(1); w2(3); w2(0);     
        w0(0); w2(9); w2(0);
        w2(0x4c); w0(pi->saved_r0);
}