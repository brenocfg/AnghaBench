#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  scr_stat ;
struct TYPE_2__ {int /*<<< orphan*/  te_refcount; } ;

/* Variables and functions */
#define  SC_TE_COLD_INIT 129 
#define  SC_TE_WARM_INIT 128 
 TYPE_1__ sc_term_dumb ; 

__attribute__((used)) static int
dumb_init(scr_stat *scp, void **softc, int code)
{
	switch (code) {
	case SC_TE_COLD_INIT:
		++sc_term_dumb.te_refcount;
		break;
	case SC_TE_WARM_INIT:
		break;
	}
	return 0;
}