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
typedef  int /*<<< orphan*/  uint32_t ;
struct sbuf {int dummy; } ;
struct TYPE_2__ {int cim_la_size; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_UP_UP_DBG_LA_CFG ; 
 scalar_t__ CHELSIO_T6 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_CXGBE ; 
 int M_NOWAIT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ chip_id (struct adapter*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sbuf_cim_la4 (struct adapter*,struct sbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_cim_la6 (struct adapter*,struct sbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int t4_cim_read (struct adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int t4_cim_read_la (struct adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sbuf_cim_la(struct adapter *sc, struct sbuf *sb, int flags)
{
	uint32_t cfg, *buf;
	int rc;

	rc = -t4_cim_read(sc, A_UP_UP_DBG_LA_CFG, 1, &cfg);
	if (rc != 0)
		return (rc);

	MPASS(flags == M_WAITOK || flags == M_NOWAIT);
	buf = malloc(sc->params.cim_la_size * sizeof(uint32_t), M_CXGBE,
	    M_ZERO | flags);
	if (buf == NULL)
		return (ENOMEM);

	rc = -t4_cim_read_la(sc, buf, NULL);
	if (rc != 0)
		goto done;
	if (chip_id(sc) < CHELSIO_T6)
		sbuf_cim_la4(sc, sb, buf, cfg);
	else
		sbuf_cim_la6(sc, sb, buf, cfg);

done:
	free(buf, M_CXGBE);
	return (rc);
}