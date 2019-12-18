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
 int /*<<< orphan*/  P2 ; 
 int* cont_map ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 
 int /*<<< orphan*/  w4 (int) ; 

__attribute__((used)) static void dstr_write_regr(  PIA *pi, int cont, int regr, int val )

{       int  r;

        r = regr + cont_map[cont];

	w0(0x81); P1; 
	if (pi->mode >= 2) { w0(0x11); } else { w0(1); }
	P2; w0(r); P1;
	
        switch (pi->mode)  {

        case 0:
        case 1: w0(val); w2(5); w2(7); w2(5); w2(4);
		break;

	case 2:
	case 3:
        case 4: w4(val); 
                break;
        }
}