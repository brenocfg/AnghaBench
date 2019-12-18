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
 int* cont_map ; 
 int j44 (int,int) ; 
 int r0 () ; 
 int r1 () ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static int aten_read_regr( PIA *pi, int cont, int regr )

{	int  a, b, r;

        r = regr + cont_map[cont] + 0x40;

	switch (pi->mode) {

        case 0: w0(r); w2(0xe); w2(6); 
		w2(7); w2(6); w2(0);
		a = r1(); w0(0x10); b = r1(); w2(0xc);
		return j44(a,b);

        case 1: r |= 0x10;
		w0(r); w2(0xe); w2(6); w0(0xff); 
		w2(0x27); w2(0x26); w2(0x20);
		a = r0();
		w2(0x26); w2(0xc);
		return a;
	}
	return -1;
}