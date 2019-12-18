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
typedef  scalar_t__ uint16_t ;
struct rsocket {scalar_t__ sq_size; scalar_t__ rq_size; int /*<<< orphan*/  cm_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  RS_QP_MAX_SIZE ; 
 scalar_t__ RS_QP_MIN_SIZE ; 
 scalar_t__ min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucma_max_qpsize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rs_set_qp_size(struct rsocket *rs)
{
	uint16_t max_size;

	max_size = min(ucma_max_qpsize(rs->cm_id), RS_QP_MAX_SIZE);

	if (rs->sq_size > max_size)
		rs->sq_size = max_size;
	else if (rs->sq_size < RS_QP_MIN_SIZE)
		rs->sq_size = RS_QP_MIN_SIZE;

	if (rs->rq_size > max_size)
		rs->rq_size = max_size;
	else if (rs->rq_size < RS_QP_MIN_SIZE)
		rs->rq_size = RS_QP_MIN_SIZE;
}