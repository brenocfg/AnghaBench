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
 int /*<<< orphan*/  P1 ; 
 int* cont_map ; 
 int j44 (int,int) ; 
 int r0 () ; 
 int r1 () ; 
 int r4 () ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 
 int /*<<< orphan*/  w3 (int) ; 

__attribute__((used)) static int comm_read_regr( PIA *pi, int cont, int regr )

{       int     l, h, r;

        r = regr + cont_map[cont];

        switch (pi->mode)  {

        case 0: w0(r); P1; w0(0);
        	w2(6); l = r1(); w0(0x80); h = r1(); w2(4);
                return j44(l,h);

        case 1: w0(r+0x20); P1; 
        	w0(0); w2(0x26); h = r0(); w2(4);
                return h;

	case 2:
	case 3:
        case 4: w3(r+0x20); (void)r1();
        	w2(0x24); h = r4(); w2(4);
                return h;

        }
        return -1;
}