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
 char j44 (int,int) ; 
 int r1 () ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static void fit2_read_block( PIA *pi, char * buf, int count )

{	int  k, a, b, c, d;

	w2(0xc); w0(0x10);

	for (k=0;k<count/4;k++) {

		w2(4); w2(5);
		w0(0); a = r1(); w0(1); b = r1();
		w0(3); c = r1(); w0(2); d = r1(); 
		buf[4*k+0] = j44(a,b);
		buf[4*k+1] = j44(d,c);

                w2(4); w2(5);
                       a = r1(); w0(3); b = r1();
                w0(1); c = r1(); w0(0); d = r1(); 
                buf[4*k+2] = j44(d,c);
                buf[4*k+3] = j44(a,b);

	}

	w2(4);

}