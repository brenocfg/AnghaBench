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
 int r0 () ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static int bpck_test_port ( PIA *pi ) 	/* check for 8-bit port */

{	int	i, r, m;

	w2(0x2c); i = r0(); w0(255-i); r = r0(); w0(i);
	m = -1;
	if (r == i) m = 2;
	if (r == (255-i)) m = 0;

	w2(0xc); i = r0(); w0(255-i); r = r0(); w0(i);
	if (r != (255-i)) m = -1;
	
	if (m == 0) { w2(6); w2(0xc); r = r0(); w0(0xaa); w0(r); w0(0xaa); }
	if (m == 2) { w2(0x26); w2(0xc); }

	if (m == -1) return 0;
	return 5;
}