#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PIA ;

/* Variables and functions */
 int j44 (int,int) ; 
 int r1 () ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static int fit2_read_regr( PIA *pi, int cont, int regr )

{	int  a, b, r;

	if (cont) {
	  if (regr != 6) return 0xff;
	  r = 7;
	} else r = regr + 0x10;

	w2(0xc); w0(r); w2(4); w2(5); 
	         w0(0); a = r1();
	         w0(1); b = r1();
	w2(4);

	return j44(a,b);

}