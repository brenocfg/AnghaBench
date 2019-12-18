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
typedef  int uint32_t ;
struct edac_device_ctl_info {struct aurora_l2_drvdata* pvt_info; } ;
struct aurora_l2_drvdata {char* msg; scalar_t__ base; } ;

/* Variables and functions */
 int AURORA_ERR_ADDR_CAP_ADDR_MASK ; 
 scalar_t__ AURORA_ERR_ADDR_CAP_REG ; 
 scalar_t__ AURORA_ERR_ATTR_CAP_REG ; 
 int AURORA_ERR_ATTR_CAP_VALID ; 
 int AURORA_ERR_ATTR_ERR_MSK ; 
 int AURORA_ERR_ATTR_ERR_OFF ; 
 int AURORA_ERR_ATTR_SRC_MSK ; 
 int AURORA_ERR_ATTR_SRC_OFF ; 
 int AURORA_ERR_ATTR_TXN_MSK ; 
 int AURORA_ERR_ATTR_TXN_OFF ; 
 int AURORA_ERR_CNT_CE_MASK ; 
 int AURORA_ERR_CNT_CE_OFFSET ; 
 int AURORA_ERR_CNT_CLR ; 
 scalar_t__ AURORA_ERR_CNT_REG ; 
 int AURORA_ERR_CNT_UE_MASK ; 
 int AURORA_ERR_CNT_UE_OFFSET ; 
 scalar_t__ AURORA_ERR_WAY_CAP_REG ; 
 int AURORA_ERR_WAY_CAP_WAY_MASK ; 
 int AURORA_ERR_WAY_CAP_WAY_OFFSET ; 
 int AURORA_ERR_WAY_IDX_MSK ; 
 int AURORA_ERR_WAY_IDX_OFF ; 
 int /*<<< orphan*/  edac_device_handle_ce (struct edac_device_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  edac_device_handle_ue (struct edac_device_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 
 scalar_t__ snprintf (char*,size_t,char*,...) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void aurora_l2_check(struct edac_device_ctl_info *dci)
{
	struct aurora_l2_drvdata *drvdata = dci->pvt_info;
	uint32_t cnt, src, txn, err, attr_cap, addr_cap, way_cap;
	unsigned int cnt_ce, cnt_ue;
	char *msg = drvdata->msg;
	size_t size = sizeof(drvdata->msg);
	size_t len = 0;

	cnt = readl(drvdata->base + AURORA_ERR_CNT_REG);
	attr_cap = readl(drvdata->base + AURORA_ERR_ATTR_CAP_REG);
	addr_cap = readl(drvdata->base + AURORA_ERR_ADDR_CAP_REG);
	way_cap = readl(drvdata->base + AURORA_ERR_WAY_CAP_REG);

	cnt_ce = (cnt & AURORA_ERR_CNT_CE_MASK) >> AURORA_ERR_CNT_CE_OFFSET;
	cnt_ue = (cnt & AURORA_ERR_CNT_UE_MASK) >> AURORA_ERR_CNT_UE_OFFSET;
	/* clear error counter registers */
	if (cnt_ce || cnt_ue)
		writel(AURORA_ERR_CNT_CLR, drvdata->base + AURORA_ERR_CNT_REG);

	if (!(attr_cap & AURORA_ERR_ATTR_CAP_VALID))
		goto clear_remaining;

	src = (attr_cap & AURORA_ERR_ATTR_SRC_MSK) >> AURORA_ERR_ATTR_SRC_OFF;
	if (src <= 3)
		len += snprintf(msg+len, size-len, "src=CPU%d ", src);
	else
		len += snprintf(msg+len, size-len, "src=IO ");

	txn =  (attr_cap & AURORA_ERR_ATTR_TXN_MSK) >> AURORA_ERR_ATTR_TXN_OFF;
	switch (txn) {
	case 0:
		len += snprintf(msg+len, size-len, "txn=Data-Read ");
		break;
	case 1:
		len += snprintf(msg+len, size-len, "txn=Isn-Read ");
		break;
	case 2:
		len += snprintf(msg+len, size-len, "txn=Clean-Flush ");
		break;
	case 3:
		len += snprintf(msg+len, size-len, "txn=Eviction ");
		break;
	case 4:
		len += snprintf(msg+len, size-len,
				"txn=Read-Modify-Write ");
		break;
	}

	err = (attr_cap & AURORA_ERR_ATTR_ERR_MSK) >> AURORA_ERR_ATTR_ERR_OFF;
	switch (err) {
	case 0:
		len += snprintf(msg+len, size-len, "err=CorrECC ");
		break;
	case 1:
		len += snprintf(msg+len, size-len, "err=UnCorrECC ");
		break;
	case 2:
		len += snprintf(msg+len, size-len, "err=TagParity ");
		break;
	}

	len += snprintf(msg+len, size-len, "addr=0x%x ", addr_cap & AURORA_ERR_ADDR_CAP_ADDR_MASK);
	len += snprintf(msg+len, size-len, "index=0x%x ", (way_cap & AURORA_ERR_WAY_IDX_MSK) >> AURORA_ERR_WAY_IDX_OFF);
	len += snprintf(msg+len, size-len, "way=0x%x", (way_cap & AURORA_ERR_WAY_CAP_WAY_MASK) >> AURORA_ERR_WAY_CAP_WAY_OFFSET);

	/* clear error capture registers */
	writel(AURORA_ERR_ATTR_CAP_VALID, drvdata->base + AURORA_ERR_ATTR_CAP_REG);
	if (err) {
		/* UnCorrECC or TagParity */
		if (cnt_ue)
			cnt_ue--;
		edac_device_handle_ue(dci, 0, 0, drvdata->msg);
	} else {
		if (cnt_ce)
			cnt_ce--;
		edac_device_handle_ce(dci, 0, 0, drvdata->msg);
	}

clear_remaining:
	/* report remaining errors */
	while (cnt_ue--)
		edac_device_handle_ue(dci, 0, 0, "details unavailable (multiple errors)");
	while (cnt_ce--)
		edac_device_handle_ue(dci, 0, 0, "details unavailable (multiple errors)");
}