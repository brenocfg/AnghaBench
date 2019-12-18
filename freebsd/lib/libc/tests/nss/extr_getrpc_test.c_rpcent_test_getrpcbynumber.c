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
struct rpcent {int /*<<< orphan*/  r_number; } ;

/* Variables and functions */
 scalar_t__ compare_rpcent (struct rpcent*,struct rpcent*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_rpcent (struct rpcent*) ; 
 struct rpcent* getrpcbynumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ rpcent_check_ambiguity (struct rpcent_test_data*,struct rpcent*) ; 
 scalar_t__ rpcent_test_correctness (struct rpcent*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rpcent_test_getrpcbynumber(struct rpcent *rpc_model, void *mdata)
{
	struct rpcent *rpc;

	printf("testing getrpcbyport() with the following data...\n");
	dump_rpcent(rpc_model);

	rpc = getrpcbynumber(rpc_model->r_number);
	if (rpcent_test_correctness(rpc, NULL) != 0 ||
	    (compare_rpcent(rpc, rpc_model, NULL) != 0 &&
	     rpcent_check_ambiguity((struct rpcent_test_data *)mdata, rpc)
	    != 0)) {
		printf("not ok\n");
		return (-1);
	} else {
		printf("ok\n");
		return (0);
	}
}