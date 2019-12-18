#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {scalar_t__ pci_func; } ;
typedef  TYPE_1__ qla_host_t ;

/* Variables and functions */
 int Q81_INVALID_NUM ; 
 int Q81_NIC1_FUNC_ENABLE ; 
 int Q81_NIC1_FUNC_MASK ; 
 int Q81_NIC1_FUNC_SHIFT ; 
 int Q81_NIC2_FUNC_ENABLE ; 
 int Q81_NIC2_FUNC_MASK ; 
 int Q81_NIC2_FUNC_SHIFT ; 
 int /*<<< orphan*/  Q81_TEST_LOGIC_FUNC_PORT_CONFIG ; 
 int qls_rd_mpi_reg (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static uint32_t
qls_get_other_fnum(qla_host_t *ha)
{
	int		ret;
	uint32_t	o_func;
	uint32_t	test_logic;
	uint32_t	nic1_fnum = Q81_INVALID_NUM;
	uint32_t	nic2_fnum = Q81_INVALID_NUM;

	ret = qls_rd_mpi_reg(ha, Q81_TEST_LOGIC_FUNC_PORT_CONFIG, &test_logic);
	if (ret)
		return(Q81_INVALID_NUM);

	if (test_logic & Q81_NIC1_FUNC_ENABLE)
		nic1_fnum = (test_logic & Q81_NIC1_FUNC_MASK) >>
					Q81_NIC1_FUNC_SHIFT;

	if (test_logic & Q81_NIC2_FUNC_ENABLE)
		nic2_fnum = (test_logic & Q81_NIC2_FUNC_MASK) >>
					Q81_NIC2_FUNC_SHIFT;

	if (ha->pci_func == 0)
		o_func = nic2_fnum;
	else
		o_func = nic1_fnum;

	return(o_func);
}