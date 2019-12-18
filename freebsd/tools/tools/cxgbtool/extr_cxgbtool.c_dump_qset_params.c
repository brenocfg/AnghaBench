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
struct ch_qset_params {int qnum; int* txq_size; int rspq_size; int* fl_size; int cong_thres; int intr_lat; int vector; scalar_t__ qset_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_GET_QSET_PARAMS ; 
 scalar_t__ EINVAL ; 
 scalar_t__ doit (char const*,int /*<<< orphan*/ ,struct ch_qset_params*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
dump_qset_params(const char *iff_name)
{
	struct ch_qset_params qp;

	qp.qset_idx = 0;

	while (doit(iff_name, CHELSIO_GET_QSET_PARAMS, &qp) == 0) {
		if (!qp.qset_idx)
			printf("Qset   TxQ0   TxQ1   TxQ2   RspQ   RxQ0   RxQ1"
			       "  Cong  Lat   IRQ\n");
		printf("%4u %6u %6u %6u %6u %6u %6u %5u %4u %5d\n",
		       qp.qnum,
		       qp.txq_size[0], qp.txq_size[1], qp.txq_size[2],
		       qp.rspq_size, qp.fl_size[0], qp.fl_size[1],
		       qp.cong_thres, qp.intr_lat, qp.vector);
		qp.qset_idx++;
	}
	if (!qp.qset_idx || (errno && errno != EINVAL))
		err(1, "get qset parameters");
	return 0;
}