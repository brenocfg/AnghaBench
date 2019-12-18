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
 int /*<<< orphan*/  o2 () ; 
 int /*<<< orphan*/  t2 (int) ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static void bpck_write_regr( PIA *pi, int cont, int regr, int val )

{	int	r;

        r = regr + cont_map[cont];

	switch (pi->mode) {

	case 0:
	case 1: w0(r);
		t2(2);
		w0(val);
		o2(); t2(4); t2(1);
		break;

	case 2:
	case 3:
	case 4: w0(r); w2(9); w2(0);
		w0(val); w2(1); w2(3); w2(0);
		break;

	}
}