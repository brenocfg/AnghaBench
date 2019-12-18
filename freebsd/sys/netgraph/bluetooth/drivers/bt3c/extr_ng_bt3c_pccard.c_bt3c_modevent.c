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
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 char* NG_BT3C_NODE_TYPE ; 
 int ng_newtype (int /*<<< orphan*/ *) ; 
 int ng_rmtype (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int /*<<< orphan*/  typestruct ; 

__attribute__((used)) static int
bt3c_modevent(module_t mod, int event, void *data)
{
	int	error;
 
	switch (event) {
	case MOD_LOAD:
		error = ng_newtype(&typestruct);
		if (error != 0)
			printf("%s: Could not register Netgraph node type, " \
				"error=%d\n", NG_BT3C_NODE_TYPE, error);
		break;

	case MOD_UNLOAD:
		error = ng_rmtype(&typestruct);
		break;

	default:
		error = EOPNOTSUPP;
		break;
	}

	return (error);
}