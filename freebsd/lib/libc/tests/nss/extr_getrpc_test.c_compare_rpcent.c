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
struct rpcent {char* r_name; scalar_t__ r_number; char** r_aliases; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_rpcent (struct rpcent*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static  int
compare_rpcent(struct rpcent *rpc1, struct rpcent *rpc2, void *mdata)
{
	char **c1, **c2;

	if (rpc1 == rpc2)
		return 0;

	if ((rpc1 == NULL) || (rpc2 == NULL))
		goto errfin;

	if ((strcmp(rpc1->r_name, rpc2->r_name) != 0) ||
		(rpc1->r_number != rpc2->r_number))
			goto errfin;

	c1 = rpc1->r_aliases;
	c2 = rpc2->r_aliases;

	if ((rpc1->r_aliases == NULL) || (rpc2->r_aliases == NULL))
		goto errfin;

	for (;*c1 && *c2; ++c1, ++c2)
		if (strcmp(*c1, *c2) != 0)
			goto errfin;

	if ((*c1 != NULL) || (*c2 != NULL))
		goto errfin;

	return 0;

errfin:
	if (mdata == NULL) {
		printf("following structures are not equal:\n");
		dump_rpcent(rpc1);
		dump_rpcent(rpc2);
	}

	return (-1);
}