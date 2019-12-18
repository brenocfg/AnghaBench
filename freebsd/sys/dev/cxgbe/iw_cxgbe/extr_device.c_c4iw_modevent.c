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
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int c4iw_mod_load () ; 
 int c4iw_mod_unload () ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
c4iw_modevent(module_t mod, int cmd, void *arg)
{
	int rc = 0;

#ifdef TCP_OFFLOAD
	switch (cmd) {
	case MOD_LOAD:
		rc = c4iw_mod_load();
		if (rc == 0)
			printf("iw_cxgbe: Chelsio T5/T6 RDMA driver loaded.\n");
		break;

	case MOD_UNLOAD:
		rc = c4iw_mod_unload();
		break;

	default:
		rc = EINVAL;
	}
#else
	printf("t4_tom: compiled without TCP_OFFLOAD support.\n");
	rc = EOPNOTSUPP;
#endif
	return (rc);
}