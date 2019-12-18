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
struct rpcent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_DATA_APPEND (int /*<<< orphan*/ ,struct rpcent_test_data*,struct rpcent*) ; 
 int /*<<< orphan*/  endrpcent () ; 
 struct rpcent* getrpcent () ; 
 int /*<<< orphan*/  rpcent ; 
 scalar_t__ rpcent_test_correctness (struct rpcent*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setrpcent (int) ; 

__attribute__((used)) static int
rpcent_fill_test_data(struct rpcent_test_data *td)
{
	struct rpcent *rpc;

	setrpcent(1);
	while ((rpc = getrpcent()) != NULL) {
		if (rpcent_test_correctness(rpc, NULL) == 0)
			TEST_DATA_APPEND(rpcent, td, rpc);
		else
			return (-1);
	}
	endrpcent();

	return (0);
}