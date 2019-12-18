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

/* Variables and functions */
 int /*<<< orphan*/  RDMA_INLINE ; 
 int /*<<< orphan*/  RDMA_RQSIZE ; 
 int /*<<< orphan*/  RDMA_SQSIZE ; 
 int /*<<< orphan*/  SOL_RDMA ; 
 scalar_t__ rq_size ; 
 int /*<<< orphan*/  rsetsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ sq_inline ; 
 scalar_t__ sq_size ; 

__attribute__((used)) static void set_rsocket_options(int rsocket)
{
	if (sq_size)
		rsetsockopt(rsocket, SOL_RDMA, RDMA_SQSIZE, &sq_size, sizeof sq_size);

	if (rq_size)
		rsetsockopt(rsocket, SOL_RDMA, RDMA_RQSIZE, &rq_size, sizeof rq_size);

	if (sq_inline)
		rsetsockopt(rsocket, SOL_RDMA, RDMA_INLINE, &sq_inline, sizeof sq_inline);
}