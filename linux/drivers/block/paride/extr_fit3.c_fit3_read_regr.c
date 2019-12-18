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
 int r0 () ; 
 int r1 () ; 
 int r4 () ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static int fit3_read_regr( PIA *pi, int cont, int regr )

{	int  a, b;

	if (cont) {
	  if (regr != 6) return 0xff;
	  regr = 7;
	} 

	switch (pi->mode) {

	case 0: w2(0xc); w0(regr + 0x10); w2(0x8); w2(0xc);
		w2(0xd); a = r1();
		w2(0xf); b = r1(); 
		w2(0xc);
		return j44(a,b);

	case 1: w2(0xc); w0(regr + 0x90); w2(0x8); w2(0xc);
		w2(0xec); w2(0xee); w2(0xef); a = r0(); 
		w2(0xc);
		return a;

	case 2: w2(0xc); w0(regr + 0x90); w2(0x8); w2(0xc); 
		w2(0xec); 
		a = r4(); b = r4(); 
		w2(0xc);
		return a;

	}
	return -1; 

}