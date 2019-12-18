#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  module_t ;
struct TYPE_4__ {char* rs_ident; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  MOD_LOAD 130 
#define  MOD_SHUTDOWN 129 
#define  MOD_UNLOAD 128 
 int PPC_FEATURE2_DARN ; 
 int cpu_features2 ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 TYPE_1__ random_darn ; 
 int /*<<< orphan*/  random_source_deregister (TYPE_1__*) ; 
 int /*<<< orphan*/  random_source_register (TYPE_1__*) ; 

__attribute__((used)) static int
darn_modevent(module_t mod, int type, void *unused)
{
	int error = 0;

	switch (type) {
	case MOD_LOAD:
		if (cpu_features2 & PPC_FEATURE2_DARN) {
			random_source_register(&random_darn);
			printf("random: fast provider: \"%s\"\n", random_darn.rs_ident);
		}
		break;

	case MOD_UNLOAD:
		if (cpu_features2 & PPC_FEATURE2_DARN)
			random_source_deregister(&random_darn);
		break;

	case MOD_SHUTDOWN:
		break;

	default:
		error = EOPNOTSUPP;
		break;

	}

	return (error);
}