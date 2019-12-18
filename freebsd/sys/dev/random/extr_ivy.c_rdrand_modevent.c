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
 int /*<<< orphan*/  has_rdrand ; 
 int /*<<< orphan*/  has_rdseed ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 TYPE_1__ random_ivy ; 
 int /*<<< orphan*/  random_source_deregister (TYPE_1__*) ; 
 int /*<<< orphan*/  random_source_register (TYPE_1__*) ; 

__attribute__((used)) static int
rdrand_modevent(module_t mod, int type, void *unused)
{
	int error = 0;

	switch (type) {
	case MOD_LOAD:
		if (has_rdrand || has_rdseed) {
			random_source_register(&random_ivy);
			printf("random: fast provider: \"%s\"\n", random_ivy.rs_ident);
		}
		break;

	case MOD_UNLOAD:
		if (has_rdrand || has_rdseed)
			random_source_deregister(&random_ivy);
		break;

	case MOD_SHUTDOWN:
		break;

	default:
		error = EOPNOTSUPP;
		break;

	}

	return (error);
}