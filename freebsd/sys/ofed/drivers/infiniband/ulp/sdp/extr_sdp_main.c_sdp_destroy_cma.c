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
struct sdp_sock {int /*<<< orphan*/ * id; } ;

/* Variables and functions */
 int /*<<< orphan*/  rdma_destroy_id (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sdp_destroy_cma(struct sdp_sock *ssk)
{

	if (ssk->id == NULL)
		return;
	rdma_destroy_id(ssk->id);
	ssk->id = NULL;
}