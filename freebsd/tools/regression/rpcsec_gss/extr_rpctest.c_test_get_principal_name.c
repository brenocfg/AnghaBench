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
typedef  int /*<<< orphan*/  rpc_gss_principal_t ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_principal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ rpc_gss_get_principal_name (int /*<<< orphan*/ *,char const*,char const*,char const*,char const*) ; 

__attribute__((used)) static void
test_get_principal_name(int argc, const char **argv)
{
	const char *mechname, *name, *node, *domain;
	rpc_gss_principal_t principal;

	if (argc < 3 || argc > 5) {
		printf("usage: rpctest principal <mechname> <name> "
		    "[<node> [<domain>] ]\n");
		exit(1);
	}

	mechname = argv[1];
	name = argv[2];
	node = NULL;
	domain = NULL;
	if (argc > 3) {
		node = argv[3];
		if (argc > 4)
			domain = argv[4];
	}

	if (rpc_gss_get_principal_name(&principal, mechname, name,
		node, domain)) {
		printf("succeeded:\n");
		print_principal(principal);
		free(principal);
	} else {
		printf("failed\n");
	}
}