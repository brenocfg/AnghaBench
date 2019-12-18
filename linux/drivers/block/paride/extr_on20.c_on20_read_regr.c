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
 int j44 (int,int) ; 
 int /*<<< orphan*/  op (int) ; 
 int r0 () ; 
 int r1 () ; 
 int /*<<< orphan*/  vl (int) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static int on20_read_regr( PIA *pi, int cont, int regr )

{	int h,l, r ;

        r = (regr<<2) + 1 + cont;

        op(1); vl(r); op(0);

	switch (pi->mode)  {

        case 0:  w2(4); w2(6); l = r1();
                 w2(4); w2(6); h = r1();
                 w2(4); w2(6); w2(4); w2(6); w2(4);
		 return j44(l,h);

	case 1:  w2(4); w2(0x26); r = r0(); 
                 w2(4); w2(0x26); w2(4);
		 return r;

	}
	return -1;
}