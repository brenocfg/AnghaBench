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
struct amd_ntb_softc {scalar_t__ conn_type; } ;

/* Variables and functions */
 scalar_t__ NTB_CONN_PRI ; 
 scalar_t__ amd_ntb_get_topo (struct amd_ntb_softc*) ; 
 int amd_ntb_init_dev (struct amd_ntb_softc*) ; 
 int amd_ntb_init_isr (struct amd_ntb_softc*) ; 
 int /*<<< orphan*/  amd_ntb_printf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int
amd_ntb_init(struct amd_ntb_softc *ntb)
{
	int rc = 0;

	ntb->conn_type = amd_ntb_get_topo(ntb);
	amd_ntb_printf(0, "AMD NTB Side: %s\n",
	    (ntb->conn_type == NTB_CONN_PRI)? "PRIMARY" : "SECONDARY");

	rc = amd_ntb_init_dev(ntb);
	if (rc != 0)
		return (rc);

	rc = amd_ntb_init_isr(ntb);
	if (rc != 0)
		return (rc);

	return (0);
}