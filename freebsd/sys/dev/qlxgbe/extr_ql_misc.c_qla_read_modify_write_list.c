#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  qla_host_t ;
typedef  int /*<<< orphan*/  q8_rdmwr_hdr_t ;
struct TYPE_4__ {int /*<<< orphan*/  wr_addr; int /*<<< orphan*/  rd_addr; } ;
typedef  TYPE_1__ q8_rdmwr_e_t ;
struct TYPE_5__ {int opcount; scalar_t__ delay_to; } ;
typedef  TYPE_2__ q8_ce_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (scalar_t__) ; 
 scalar_t__ qla_rdmwr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qla_read_modify_write_list(qla_host_t *ha, q8_ce_hdr_t *ce_hdr)
{
	int		i;
	q8_rdmwr_hdr_t	*rdmwr_hdr;
	q8_rdmwr_e_t	*rdmwr_e;

	rdmwr_hdr = (q8_rdmwr_hdr_t *)((uint8_t *)ce_hdr +
						sizeof (q8_ce_hdr_t));
	rdmwr_e = (q8_rdmwr_e_t *)((uint8_t *)rdmwr_hdr +
					sizeof(q8_rdmwr_hdr_t));

	for (i = 0; i < ce_hdr->opcount; i++, rdmwr_e++) {

		if (qla_rdmwr(ha, rdmwr_e->rd_addr, rdmwr_e->wr_addr,
			rdmwr_hdr)) {
			return -1;
		}
		if (ce_hdr->delay_to) {
			DELAY(ce_hdr->delay_to);
		}
	}
	return 0;
}