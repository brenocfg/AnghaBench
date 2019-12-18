#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int member_0; int member_1; int member_2; int member_3; int /*<<< orphan*/  member_4; } ;
struct mc7_timing_params {int member_0; int member_1; int member_2; int member_4; int member_5; int member_6; int /*<<< orphan*/  RdToWrDly; int /*<<< orphan*/  WrToRdDly; int /*<<< orphan*/  BkCyc; int /*<<< orphan*/ * RefCyc; int /*<<< orphan*/  PreCyc; int /*<<< orphan*/  ActToRdWrDly; int /*<<< orphan*/  ActToPreDly; TYPE_1__ member_3; } ;
struct mc7 {unsigned int size; scalar_t__ offset; int /*<<< orphan*/  name; int /*<<< orphan*/ * adapter; } ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 scalar_t__ A_MC7_BIST_ADDR_BEG ; 
 scalar_t__ A_MC7_BIST_ADDR_END ; 
 scalar_t__ A_MC7_BIST_DATA ; 
 scalar_t__ A_MC7_BIST_OP ; 
 scalar_t__ A_MC7_CAL ; 
 scalar_t__ A_MC7_CFG ; 
 scalar_t__ A_MC7_DLL ; 
 scalar_t__ A_MC7_ECC ; 
 scalar_t__ A_MC7_EXT_MODE1 ; 
 scalar_t__ A_MC7_EXT_MODE2 ; 
 scalar_t__ A_MC7_EXT_MODE3 ; 
 scalar_t__ A_MC7_MODE ; 
 scalar_t__ A_MC7_PARM ; 
 scalar_t__ A_MC7_PRE ; 
 scalar_t__ A_MC7_REF ; 
 int /*<<< orphan*/  CH_ERR (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int F_BUSY ; 
 int F_CAL_FAULT ; 
 int F_CLKEN ; 
 int /*<<< orphan*/  F_DLLENB ; 
 int /*<<< orphan*/  F_DLLRST ; 
 unsigned int F_ECCCHKEN ; 
 unsigned int F_ECCGENEN ; 
 int F_IFEN ; 
 unsigned int F_PERREFEN ; 
 int /*<<< orphan*/  F_RDY ; 
 int F_SGL_CAL_EN ; 
 int F_SLOW ; 
 int F_TERM150 ; 
 unsigned int G_DEN (int) ; 
 unsigned int G_WIDTH (int) ; 
 unsigned int V_ACTTOPREDLY (int /*<<< orphan*/ ) ; 
 unsigned int V_ACTTORDWRDLY (int /*<<< orphan*/ ) ; 
 unsigned int V_BKCYC (int /*<<< orphan*/ ) ; 
 unsigned int V_OP (int) ; 
 unsigned int V_PRECYC (int /*<<< orphan*/ ) ; 
 unsigned int V_PREREFDIV (unsigned int) ; 
 unsigned int V_RDTOWRDLY (int /*<<< orphan*/ ) ; 
 unsigned int V_REFCYC (int /*<<< orphan*/ ) ; 
 unsigned int V_WRTORDDLY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int t3_read_reg (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  t3_set_reg_field (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_write_reg (int /*<<< orphan*/ *,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ wrreg_wait (int /*<<< orphan*/ *,scalar_t__,unsigned int const) ; 

__attribute__((used)) static int mc7_init(struct mc7 *mc7, unsigned int mc7_clock, int mem_type)
{
	static const unsigned int mc7_mode[] = {
		0x632, 0x642, 0x652, 0x432, 0x442
	};
	static const struct mc7_timing_params mc7_timings[] = {
		{ 12, 3, 4, { 20, 28, 34, 52, 0 }, 15, 6, 4 },
		{ 12, 4, 5, { 20, 28, 34, 52, 0 }, 16, 7, 4 },
		{ 12, 5, 6, { 20, 28, 34, 52, 0 }, 17, 8, 4 },
		{ 9,  3, 4, { 15, 21, 26, 39, 0 }, 12, 6, 4 },
		{ 9,  4, 5, { 15, 21, 26, 39, 0 }, 13, 7, 4 }
	};

	u32 val;
	unsigned int width, density, slow, attempts;
	adapter_t *adapter = mc7->adapter;
	const struct mc7_timing_params *p = &mc7_timings[mem_type];

	if (!mc7->size)
		return 0;

	val = t3_read_reg(adapter, mc7->offset + A_MC7_CFG);
	slow = val & F_SLOW;
	width = G_WIDTH(val);
	density = G_DEN(val);

	t3_write_reg(adapter, mc7->offset + A_MC7_CFG, val | F_IFEN);
	val = t3_read_reg(adapter, mc7->offset + A_MC7_CFG);  /* flush */
	msleep(1);

	if (!slow) {
		t3_write_reg(adapter, mc7->offset + A_MC7_CAL, F_SGL_CAL_EN);
		(void) t3_read_reg(adapter, mc7->offset + A_MC7_CAL);
		msleep(1);
		if (t3_read_reg(adapter, mc7->offset + A_MC7_CAL) &
		    (F_BUSY | F_SGL_CAL_EN | F_CAL_FAULT)) {
			CH_ERR(adapter, "%s MC7 calibration timed out\n",
			       mc7->name);
			goto out_fail;
		}
	}

	t3_write_reg(adapter, mc7->offset + A_MC7_PARM,
		     V_ACTTOPREDLY(p->ActToPreDly) |
		     V_ACTTORDWRDLY(p->ActToRdWrDly) | V_PRECYC(p->PreCyc) |
		     V_REFCYC(p->RefCyc[density]) | V_BKCYC(p->BkCyc) |
		     V_WRTORDDLY(p->WrToRdDly) | V_RDTOWRDLY(p->RdToWrDly));

	t3_write_reg(adapter, mc7->offset + A_MC7_CFG,
		     val | F_CLKEN | F_TERM150);
	(void) t3_read_reg(adapter, mc7->offset + A_MC7_CFG); /* flush */

	if (!slow)
		t3_set_reg_field(adapter, mc7->offset + A_MC7_DLL, F_DLLENB,
				 F_DLLENB);
	udelay(1);

	val = slow ? 3 : 6;
	if (wrreg_wait(adapter, mc7->offset + A_MC7_PRE, 0) ||
	    wrreg_wait(adapter, mc7->offset + A_MC7_EXT_MODE2, 0) ||
	    wrreg_wait(adapter, mc7->offset + A_MC7_EXT_MODE3, 0) ||
	    wrreg_wait(adapter, mc7->offset + A_MC7_EXT_MODE1, val))
		goto out_fail;

	if (!slow) {
		t3_write_reg(adapter, mc7->offset + A_MC7_MODE, 0x100);
		t3_set_reg_field(adapter, mc7->offset + A_MC7_DLL,
				 F_DLLRST, 0);
		udelay(5);
	}

	if (wrreg_wait(adapter, mc7->offset + A_MC7_PRE, 0) ||
	    wrreg_wait(adapter, mc7->offset + A_MC7_REF, 0) ||
	    wrreg_wait(adapter, mc7->offset + A_MC7_REF, 0) ||
	    wrreg_wait(adapter, mc7->offset + A_MC7_MODE,
		       mc7_mode[mem_type]) ||
	    wrreg_wait(adapter, mc7->offset + A_MC7_EXT_MODE1, val | 0x380) ||
	    wrreg_wait(adapter, mc7->offset + A_MC7_EXT_MODE1, val))
		goto out_fail;

	/* clock value is in KHz */
	mc7_clock = mc7_clock * 7812 + mc7_clock / 2;  /* ns */
	mc7_clock /= 1000000;                          /* KHz->MHz, ns->us */

	t3_write_reg(adapter, mc7->offset + A_MC7_REF,
		     F_PERREFEN | V_PREREFDIV(mc7_clock));
	(void) t3_read_reg(adapter, mc7->offset + A_MC7_REF); /* flush */

	t3_write_reg(adapter, mc7->offset + A_MC7_ECC,
		     F_ECCGENEN | F_ECCCHKEN);
	t3_write_reg(adapter, mc7->offset + A_MC7_BIST_DATA, 0);
	t3_write_reg(adapter, mc7->offset + A_MC7_BIST_ADDR_BEG, 0);
	t3_write_reg(adapter, mc7->offset + A_MC7_BIST_ADDR_END,
		     (mc7->size << width) - 1);
	t3_write_reg(adapter, mc7->offset + A_MC7_BIST_OP, V_OP(1));
	(void) t3_read_reg(adapter, mc7->offset + A_MC7_BIST_OP); /* flush */

	attempts = 50;
	do {
		msleep(250);
		val = t3_read_reg(adapter, mc7->offset + A_MC7_BIST_OP);
	} while ((val & F_BUSY) && --attempts);
	if (val & F_BUSY) {
		CH_ERR(adapter, "%s MC7 BIST timed out\n", mc7->name);
		goto out_fail;
	}

	/* Enable normal memory accesses. */
	t3_set_reg_field(adapter, mc7->offset + A_MC7_CFG, 0, F_RDY);
	return 0;

 out_fail:
	return -1;
}