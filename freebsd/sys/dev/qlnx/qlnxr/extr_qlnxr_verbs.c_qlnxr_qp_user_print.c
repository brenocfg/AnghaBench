#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  buf_len; int /*<<< orphan*/  buf_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  buf_len; int /*<<< orphan*/  buf_addr; } ;
struct qlnxr_qp {TYPE_2__ urq; TYPE_1__ usq; } ;
struct qlnxr_dev {int /*<<< orphan*/  ha; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ ,char*,struct qlnxr_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
qlnxr_qp_user_print( struct qlnxr_dev *dev,
	struct qlnxr_qp *qp)
{
	QL_DPRINT12((dev->ha), "qp=%p. sq_addr=0x%llx, sq_len=%zd, "
		"rq_addr=0x%llx, rq_len=%zd\n",
		qp, qp->usq.buf_addr, qp->usq.buf_len, qp->urq.buf_addr,
		qp->urq.buf_len);
	return;
}