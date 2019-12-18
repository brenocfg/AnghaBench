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
typedef  int /*<<< orphan*/  module_t ;
struct TYPE_3__ {int nh_qlimit; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int /*<<< orphan*/  bootverbose ; 
 int /*<<< orphan*/  epair_dpcpu_init () ; 
 TYPE_1__ epair_nh ; 
 char* epairname ; 
 int ifqmaxlen ; 
 int /*<<< orphan*/  netisr_register (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int
epair_modevent(module_t mod, int type, void *data)
{
	int qlimit;

	switch (type) {
	case MOD_LOAD:
		/* For now limit us to one global mutex and one inq. */
		epair_dpcpu_init();
		epair_nh.nh_qlimit = 42 * ifqmaxlen; /* 42 shall be the number. */
		if (TUNABLE_INT_FETCH("net.link.epair.netisr_maxqlen", &qlimit))
		    epair_nh.nh_qlimit = qlimit;
		netisr_register(&epair_nh);
		if (bootverbose)
			printf("%s initialized.\n", epairname);
		break;
	case MOD_UNLOAD:
		/* Handled in epair_uninit() */
		break;
	default:
		return (EOPNOTSUPP);
	}
	return (0);
}