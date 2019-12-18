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
 int /*<<< orphan*/ * TEST_DATA_FIND (int /*<<< orphan*/ ,struct rpcent_test_data*,struct rpcent*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compare_rpcent ; 
 int /*<<< orphan*/  rpcent ; 

__attribute__((used)) static int
rpcent_check_ambiguity(struct rpcent_test_data *td, struct rpcent *rpc)
{

	return (TEST_DATA_FIND(rpcent, td, rpc, compare_rpcent,
		NULL) != NULL ? 0 : -1);
}