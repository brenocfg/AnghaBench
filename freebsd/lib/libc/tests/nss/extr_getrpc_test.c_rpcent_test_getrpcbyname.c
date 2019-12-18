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
struct rpcent_test_data {int dummy; } ;
struct rpcent {char* r_name; char** r_aliases; } ;

/* Variables and functions */
 scalar_t__ compare_rpcent (struct rpcent*,struct rpcent*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_rpcent (struct rpcent*) ; 
 struct rpcent* getrpcbyname (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ rpcent_check_ambiguity (struct rpcent_test_data*,struct rpcent*) ; 
 scalar_t__ rpcent_test_correctness (struct rpcent*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rpcent_test_getrpcbyname(struct rpcent *rpc_model, void *mdata)
{
	char **alias;
	struct rpcent *rpc;

	printf("testing getrpcbyname() with the following data:\n");
	dump_rpcent(rpc_model);

	rpc = getrpcbyname(rpc_model->r_name);
	if (rpcent_test_correctness(rpc, NULL) != 0)
		goto errfin;

	if ((compare_rpcent(rpc, rpc_model, NULL) != 0) &&
	    (rpcent_check_ambiguity((struct rpcent_test_data *)mdata, rpc)
	    !=0))
	    goto errfin;

	for (alias = rpc_model->r_aliases; *alias; ++alias) {
		rpc = getrpcbyname(*alias);

		if (rpcent_test_correctness(rpc, NULL) != 0)
			goto errfin;

		if ((compare_rpcent(rpc, rpc_model, NULL) != 0) &&
		    (rpcent_check_ambiguity(
		    (struct rpcent_test_data *)mdata, rpc) != 0))
		    goto errfin;
	}

	printf("ok\n");
	return (0);

errfin:
	printf("not ok\n");

	return (-1);
}