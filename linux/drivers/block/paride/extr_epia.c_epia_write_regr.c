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
 scalar_t__* cont_map ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 
 int /*<<< orphan*/  w3 (int) ; 
 int /*<<< orphan*/  w4 (int) ; 

__attribute__((used)) static void epia_write_regr( PIA *pi, int cont, int regr, int val)

{       int  r;

	regr += cont_map[cont];

        switch (pi->mode)  {

        case 0:
        case 1:
        case 2: r = regr^0x19;
                w0(r); w2(1); w0(val); w2(3); w2(4);
                break;

	case 3:
	case 4:
        case 5: r = regr^0x40;
                w3(r); w4(val); w2(4);
                break;
        }
}