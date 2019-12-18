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
struct ibv_grh {int dummy; } ;
struct cmatest_node {int /*<<< orphan*/  mem; int /*<<< orphan*/  mr; int /*<<< orphan*/  pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBV_ACCESS_LOCAL_WRITE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_reg_mr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc (scalar_t__) ; 
 scalar_t__ message_count ; 
 scalar_t__ message_size ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int create_message(struct cmatest_node *node)
{
	if (!message_size)
		message_count = 0;

	if (!message_count)
		return 0;

	node->mem = malloc(message_size + sizeof(struct ibv_grh));
	if (!node->mem) {
		printf("failed message allocation\n");
		return -1;
	}
	node->mr = ibv_reg_mr(node->pd, node->mem,
			      message_size + sizeof(struct ibv_grh),
			      IBV_ACCESS_LOCAL_WRITE);
	if (!node->mr) {
		printf("failed to reg MR\n");
		goto err;
	}
	return 0;
err:
	free(node->mem);
	return -1;
}