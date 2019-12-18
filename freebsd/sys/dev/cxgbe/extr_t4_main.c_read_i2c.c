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
struct t4_i2c_data {int len; scalar_t__ port_id; int /*<<< orphan*/ * data; int /*<<< orphan*/  offset; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_2__ {scalar_t__ nports; } ;
struct adapter {int /*<<< orphan*/  mbox; TYPE_1__ params; } ;

/* Variables and functions */
 int EFBIG ; 
 int EINVAL ; 
 int INTR_OK ; 
 int SLEEP_OK ; 
 int begin_synchronized_op (struct adapter*,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  end_synchronized_op (struct adapter*,int /*<<< orphan*/ ) ; 
 int t4_i2c_rd (struct adapter*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
read_i2c(struct adapter *sc, struct t4_i2c_data *i2cd)
{
	int rc;

	if (i2cd->len == 0 || i2cd->port_id >= sc->params.nports)
		return (EINVAL);

	if (i2cd->len > sizeof(i2cd->data))
		return (EFBIG);

	rc = begin_synchronized_op(sc, NULL, SLEEP_OK | INTR_OK, "t4i2crd");
	if (rc)
		return (rc);
	rc = -t4_i2c_rd(sc, sc->mbox, i2cd->port_id, i2cd->dev_addr,
	    i2cd->offset, i2cd->len, &i2cd->data[0]);
	end_synchronized_op(sc, 0);

	return (rc);
}