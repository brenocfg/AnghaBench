#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {int /*<<< orphan*/  addr_err; int /*<<< orphan*/  parity_err; int /*<<< orphan*/  uncorr_err; int /*<<< orphan*/  corr_err; } ;
struct mc7 {scalar_t__ offset; int /*<<< orphan*/  name; TYPE_2__ stats; TYPE_3__* adapter; } ;
struct TYPE_9__ {scalar_t__ rev; } ;
struct TYPE_11__ {TYPE_1__ params; } ;
typedef  TYPE_3__ adapter_t ;

/* Variables and functions */
 scalar_t__ A_MC7_CE_ADDR ; 
 scalar_t__ A_MC7_CE_DATA0 ; 
 scalar_t__ A_MC7_CE_DATA1 ; 
 scalar_t__ A_MC7_CE_DATA2 ; 
 scalar_t__ A_MC7_ERR_ADDR ; 
 scalar_t__ A_MC7_INT_CAUSE ; 
 scalar_t__ A_MC7_UE_ADDR ; 
 scalar_t__ A_MC7_UE_DATA0 ; 
 scalar_t__ A_MC7_UE_DATA1 ; 
 scalar_t__ A_MC7_UE_DATA2 ; 
 int /*<<< orphan*/  CH_ALERT (TYPE_3__*,char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  CH_WARN (TYPE_3__*,char*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int F_AE ; 
 int F_CE ; 
 int F_UE ; 
 int G_PE (int) ; 
 int MC7_INTR_FATAL ; 
 int /*<<< orphan*/  t3_fatal_err (TYPE_3__*) ; 
 int t3_read_reg (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  t3_write_reg (TYPE_3__*,scalar_t__,int) ; 

__attribute__((used)) static void mc7_intr_handler(struct mc7 *mc7)
{
	adapter_t *adapter = mc7->adapter;
	u32 cause = t3_read_reg(adapter, mc7->offset + A_MC7_INT_CAUSE);

	if (cause & F_CE) {
		mc7->stats.corr_err++;
		CH_WARN(adapter, "%s MC7 correctable error at addr 0x%x, "
			"data 0x%x 0x%x 0x%x\n", mc7->name,
			t3_read_reg(adapter, mc7->offset + A_MC7_CE_ADDR),
			t3_read_reg(adapter, mc7->offset + A_MC7_CE_DATA0),
			t3_read_reg(adapter, mc7->offset + A_MC7_CE_DATA1),
			t3_read_reg(adapter, mc7->offset + A_MC7_CE_DATA2));
	}

	if (cause & F_UE) {
		mc7->stats.uncorr_err++;
		CH_ALERT(adapter, "%s MC7 uncorrectable error at addr 0x%x, "
			 "data 0x%x 0x%x 0x%x\n", mc7->name,
			 t3_read_reg(adapter, mc7->offset + A_MC7_UE_ADDR),
			 t3_read_reg(adapter, mc7->offset + A_MC7_UE_DATA0),
			 t3_read_reg(adapter, mc7->offset + A_MC7_UE_DATA1),
			 t3_read_reg(adapter, mc7->offset + A_MC7_UE_DATA2));
	}

	if (G_PE(cause)) {
		mc7->stats.parity_err++;
		CH_ALERT(adapter, "%s MC7 parity error 0x%x\n",
			 mc7->name, G_PE(cause));
	}

	if (cause & F_AE) {
		u32 addr = 0;

		if (adapter->params.rev > 0)
			addr = t3_read_reg(adapter,
					   mc7->offset + A_MC7_ERR_ADDR);
		mc7->stats.addr_err++;
		CH_ALERT(adapter, "%s MC7 address error: 0x%x\n",
			 mc7->name, addr);
	}

	if (cause & MC7_INTR_FATAL)
		t3_fatal_err(adapter);

	t3_write_reg(adapter, mc7->offset + A_MC7_INT_CAUSE, cause);
}