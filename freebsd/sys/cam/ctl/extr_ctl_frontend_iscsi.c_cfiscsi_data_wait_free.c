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
struct cfiscsi_session {int /*<<< orphan*/  cs_conn; } ;
struct cfiscsi_data_wait {int /*<<< orphan*/  cdw_icl_prv; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfiscsi_data_wait_zone ; 
 int /*<<< orphan*/  icl_conn_transfer_done (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct cfiscsi_data_wait*) ; 

__attribute__((used)) static void
cfiscsi_data_wait_free(struct cfiscsi_session *cs,
    struct cfiscsi_data_wait *cdw)
{

	icl_conn_transfer_done(cs->cs_conn, cdw->cdw_icl_prv);
	uma_zfree(cfiscsi_data_wait_zone, cdw);
}