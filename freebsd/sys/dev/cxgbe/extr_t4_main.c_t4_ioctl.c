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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct thread {int dummy; } ;
struct t4_tracer {int dummy; } ;
struct t4_sge_context {int dummy; } ;
struct t4_sched_queue {int dummy; } ;
struct t4_sched_params {int dummy; } ;
struct t4_regdump {int len; int /*<<< orphan*/  data; } ;
struct t4_reg {int addr; int size; int val; } ;
struct t4_offload_policy {int dummy; } ;
struct t4_mem_range {int dummy; } ;
struct t4_i2c_data {int dummy; } ;
struct t4_filter {int dummy; } ;
struct t4_data {int dummy; } ;
struct t4_cudbg_dump {int dummy; } ;
struct t4_bootrom {int dummy; } ;
struct cdev {struct adapter* si_drv1; } ;
struct adapter {int mmio_len; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  CHELSIO_T4_CLEAR_STATS 149 
#define  CHELSIO_T4_CUDBG_DUMP 148 
#define  CHELSIO_T4_DEL_FILTER 147 
#define  CHELSIO_T4_GETREG 146 
#define  CHELSIO_T4_GET_FILTER 145 
#define  CHELSIO_T4_GET_FILTER_MODE 144 
#define  CHELSIO_T4_GET_I2C 143 
#define  CHELSIO_T4_GET_MEM 142 
#define  CHELSIO_T4_GET_SGE_CONTEXT 141 
#define  CHELSIO_T4_GET_TRACER 140 
#define  CHELSIO_T4_LOAD_BOOT 139 
#define  CHELSIO_T4_LOAD_BOOTCFG 138 
#define  CHELSIO_T4_LOAD_CFG 137 
#define  CHELSIO_T4_LOAD_FW 136 
#define  CHELSIO_T4_REGDUMP 135 
#define  CHELSIO_T4_SCHED_CLASS 134 
#define  CHELSIO_T4_SCHED_QUEUE 133 
#define  CHELSIO_T4_SETREG 132 
#define  CHELSIO_T4_SET_FILTER 131 
#define  CHELSIO_T4_SET_FILTER_MODE 130 
#define  CHELSIO_T4_SET_OFLD_POLICY 129 
#define  CHELSIO_T4_SET_TRACER 128 
 int EFAULT ; 
 int EINVAL ; 
 int ENOBUFS ; 
 int ENOTTY ; 
 int /*<<< orphan*/  M_CXGBE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PRIV_DRIVER ; 
 int clear_stats (struct adapter*,int /*<<< orphan*/ ) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int cudbg_dump (struct adapter*,struct t4_cudbg_dump*) ; 
 int del_filter (struct adapter*,struct t4_filter*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int get_filter (struct adapter*,struct t4_filter*) ; 
 int get_filter_mode (struct adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_regs (struct adapter*,struct t4_regdump*,int /*<<< orphan*/ *) ; 
 int get_sge_context (struct adapter*,struct t4_sge_context*) ; 
 int load_boot (struct adapter*,struct t4_bootrom*) ; 
 int load_bootcfg (struct adapter*,struct t4_data*) ; 
 int load_cfg (struct adapter*,struct t4_data*) ; 
 int load_fw (struct adapter*,struct t4_data*) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int read_card_mem (struct adapter*,int,struct t4_mem_range*) ; 
 int read_i2c (struct adapter*,struct t4_i2c_data*) ; 
 int set_filter (struct adapter*,struct t4_filter*) ; 
 int set_filter_mode (struct adapter*,int /*<<< orphan*/ ) ; 
 int set_offload_policy (struct adapter*,struct t4_offload_policy*) ; 
 int t4_get_regs_len (struct adapter*) ; 
 int t4_get_tracer (struct adapter*,struct t4_tracer*) ; 
 int t4_read_reg (struct adapter*,int) ; 
 int t4_read_reg64 (struct adapter*,int) ; 
 int t4_set_sched_class (struct adapter*,struct t4_sched_params*) ; 
 int t4_set_sched_queue (struct adapter*,struct t4_sched_queue*) ; 
 int t4_set_tracer (struct adapter*,struct t4_tracer*) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg64 (struct adapter*,int,int) ; 

__attribute__((used)) static int
t4_ioctl(struct cdev *dev, unsigned long cmd, caddr_t data, int fflag,
    struct thread *td)
{
	int rc;
	struct adapter *sc = dev->si_drv1;

	rc = priv_check(td, PRIV_DRIVER);
	if (rc != 0)
		return (rc);

	switch (cmd) {
	case CHELSIO_T4_GETREG: {
		struct t4_reg *edata = (struct t4_reg *)data;

		if ((edata->addr & 0x3) != 0 || edata->addr >= sc->mmio_len)
			return (EFAULT);

		if (edata->size == 4)
			edata->val = t4_read_reg(sc, edata->addr);
		else if (edata->size == 8)
			edata->val = t4_read_reg64(sc, edata->addr);
		else
			return (EINVAL);

		break;
	}
	case CHELSIO_T4_SETREG: {
		struct t4_reg *edata = (struct t4_reg *)data;

		if ((edata->addr & 0x3) != 0 || edata->addr >= sc->mmio_len)
			return (EFAULT);

		if (edata->size == 4) {
			if (edata->val & 0xffffffff00000000)
				return (EINVAL);
			t4_write_reg(sc, edata->addr, (uint32_t) edata->val);
		} else if (edata->size == 8)
			t4_write_reg64(sc, edata->addr, edata->val);
		else
			return (EINVAL);
		break;
	}
	case CHELSIO_T4_REGDUMP: {
		struct t4_regdump *regs = (struct t4_regdump *)data;
		int reglen = t4_get_regs_len(sc);
		uint8_t *buf;

		if (regs->len < reglen) {
			regs->len = reglen; /* hint to the caller */
			return (ENOBUFS);
		}

		regs->len = reglen;
		buf = malloc(reglen, M_CXGBE, M_WAITOK | M_ZERO);
		get_regs(sc, regs, buf);
		rc = copyout(buf, regs->data, reglen);
		free(buf, M_CXGBE);
		break;
	}
	case CHELSIO_T4_GET_FILTER_MODE:
		rc = get_filter_mode(sc, (uint32_t *)data);
		break;
	case CHELSIO_T4_SET_FILTER_MODE:
		rc = set_filter_mode(sc, *(uint32_t *)data);
		break;
	case CHELSIO_T4_GET_FILTER:
		rc = get_filter(sc, (struct t4_filter *)data);
		break;
	case CHELSIO_T4_SET_FILTER:
		rc = set_filter(sc, (struct t4_filter *)data);
		break;
	case CHELSIO_T4_DEL_FILTER:
		rc = del_filter(sc, (struct t4_filter *)data);
		break;
	case CHELSIO_T4_GET_SGE_CONTEXT:
		rc = get_sge_context(sc, (struct t4_sge_context *)data);
		break;
	case CHELSIO_T4_LOAD_FW:
		rc = load_fw(sc, (struct t4_data *)data);
		break;
	case CHELSIO_T4_GET_MEM:
		rc = read_card_mem(sc, 2, (struct t4_mem_range *)data);
		break;
	case CHELSIO_T4_GET_I2C:
		rc = read_i2c(sc, (struct t4_i2c_data *)data);
		break;
	case CHELSIO_T4_CLEAR_STATS:
		rc = clear_stats(sc, *(uint32_t *)data);
		break;
	case CHELSIO_T4_SCHED_CLASS:
		rc = t4_set_sched_class(sc, (struct t4_sched_params *)data);
		break;
	case CHELSIO_T4_SCHED_QUEUE:
		rc = t4_set_sched_queue(sc, (struct t4_sched_queue *)data);
		break;
	case CHELSIO_T4_GET_TRACER:
		rc = t4_get_tracer(sc, (struct t4_tracer *)data);
		break;
	case CHELSIO_T4_SET_TRACER:
		rc = t4_set_tracer(sc, (struct t4_tracer *)data);
		break;
	case CHELSIO_T4_LOAD_CFG:
		rc = load_cfg(sc, (struct t4_data *)data);
		break;
	case CHELSIO_T4_LOAD_BOOT:
		rc = load_boot(sc, (struct t4_bootrom *)data);
		break;
	case CHELSIO_T4_LOAD_BOOTCFG:
		rc = load_bootcfg(sc, (struct t4_data *)data);
		break;
	case CHELSIO_T4_CUDBG_DUMP:
		rc = cudbg_dump(sc, (struct t4_cudbg_dump *)data);
		break;
	case CHELSIO_T4_SET_OFLD_POLICY:
		rc = set_offload_policy(sc, (struct t4_offload_policy *)data);
		break;
	default:
		rc = ENOTTY;
	}

	return (rc);
}