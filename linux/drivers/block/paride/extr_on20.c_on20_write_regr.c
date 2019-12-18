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
 int /*<<< orphan*/  op (int) ; 
 int /*<<< orphan*/  vl (int) ; 

__attribute__((used)) static void on20_write_regr( PIA *pi, int cont, int regr, int val )

{	int r;

	r = (regr<<2) + 1 + cont;

	op(1); vl(r); 
	op(0); vl(val); 
	op(0); vl(val);
}