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
typedef  int /*<<< orphan*/  u_int ;
struct t4_bootrom {int len; int pf_offset; int pfidx_addr; int /*<<< orphan*/  data; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_PCIE_PF_EXPROM_OFST ; 
 int EFBIG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  G_OFFSET (int) ; 
 int INTR_OK ; 
 int /*<<< orphan*/  M_CXGBE ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PF_REG (int,int /*<<< orphan*/ ) ; 
 int SLEEP_OK ; 
 int begin_synchronized_op (struct adapter*,int /*<<< orphan*/ *,int,char*) ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  end_synchronized_op (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int t4_load_boot (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
load_boot(struct adapter *sc, struct t4_bootrom *br)
{
	int rc;
	uint8_t *br_data = NULL;
	u_int offset;

	if (br->len > 1024 * 1024)
		return (EFBIG);

	if (br->pf_offset == 0) {
		/* pfidx */
		if (br->pfidx_addr > 7)
			return (EINVAL);
		offset = G_OFFSET(t4_read_reg(sc, PF_REG(br->pfidx_addr,
		    A_PCIE_PF_EXPROM_OFST)));
	} else if (br->pf_offset == 1) {
		/* offset */
		offset = G_OFFSET(br->pfidx_addr);
	} else {
		return (EINVAL);
	}

	rc = begin_synchronized_op(sc, NULL, SLEEP_OK | INTR_OK, "t4ldbr");
	if (rc)
		return (rc);

	if (br->len == 0) {
		/* clear */
		rc = -t4_load_boot(sc, NULL, offset, 0);
		goto done;
	}

	br_data = malloc(br->len, M_CXGBE, M_WAITOK);
	if (br_data == NULL) {
		rc = ENOMEM;
		goto done;
	}

	rc = copyin(br->data, br_data, br->len);
	if (rc == 0)
		rc = -t4_load_boot(sc, br_data, offset, br->len);

	free(br_data, M_CXGBE);
done:
	end_synchronized_op(sc, 0);
	return (rc);
}