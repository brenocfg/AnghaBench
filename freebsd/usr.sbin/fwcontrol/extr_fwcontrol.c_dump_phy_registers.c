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
typedef  int /*<<< orphan*/  u_int8_t ;
struct phyreg_page1 {int compliance; int* vendor_id; int* product_id; } ;
struct phyreg_page0 {int astat; int bstat; int ch; int con; int rxok; int dis; int negotiated_speed; int pie; int fault; int stanby_fault; int disscrm; int b_only; int dc_connected; int max_port_speed; int lpp; int cable_speed; int connection_unreliable; int beta_mode; int port_error; int loop_disable; int in_standby; int hard_disable; } ;
struct phyreg_base {int phy_id; int r; int cps; int rhb; int ibr; int gap_count; int extended; int num_ports; int phy_speed; int delay; int lctrl; int c; int jitter; int pwr_class; int wdie; int isbr; int ctoi; int cpsi; int stoi; int pei; int eaa; int emc; int legacy_spd; int blink; int bridge; int page_select; int port_select; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  read_phy_page (int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  read_phy_registers (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
dump_phy_registers(int fd)
{
	struct phyreg_base b;
	struct phyreg_page0 p;
	struct phyreg_page1 v;
	int i;

	printf("=== base register ===\n");
	read_phy_registers(fd, (u_int8_t *)&b, 0, 8);
	printf(
	    "Physical_ID:%d  R:%d  CPS:%d\n"
	    "RHB:%d  IBR:%d  Gap_Count:%d\n"
	    "Extended:%d Num_Ports:%d\n"
	    "PHY_Speed:%d Delay:%d\n"
	    "LCtrl:%d C:%d Jitter:%d Pwr_Class:%d\n"
	    "WDIE:%d ISBR:%d CTOI:%d CPSI:%d STOI:%d PEI:%d EAA:%d EMC:%d\n"
	    "Max_Legacy_SPD:%d BLINK:%d Bridge:%d\n"
	    "Page_Select:%d Port_Select%d\n",
	    b.phy_id, b.r, b.cps,
	    b.rhb, b.ibr, b.gap_count, 
	    b.extended, b.num_ports,
	    b.phy_speed, b.delay,
	    b.lctrl, b.c, b.jitter, b.pwr_class,
	    b.wdie, b.isbr, b.ctoi, b.cpsi, b.stoi, b.pei, b.eaa, b.emc,
	    b.legacy_spd, b.blink, b.bridge,
	    b.page_select, b.port_select
	);

	for (i = 0; i < b.num_ports; i ++) {
		printf("\n=== page 0 port %d ===\n", i);
		read_phy_page(fd, (u_int8_t *)&p, 0, i);
		printf(
		    "Astat:%d BStat:%d Ch:%d Con:%d RXOK:%d Dis:%d\n"
		    "Negotiated_speed:%d PIE:%d Fault:%d Stanby_fault:%d Disscrm:%d B_Only:%d\n"
		    "DC_connected:%d Max_port_speed:%d LPP:%d Cable_speed:%d\n"
		    "Connection_unreliable:%d Beta_mode:%d\n"
		    "Port_error:0x%x\n"
		    "Loop_disable:%d In_standby:%d Hard_disable:%d\n",
		    p.astat, p.bstat, p.ch, p.con, p.rxok, p.dis,
		    p.negotiated_speed, p.pie, p.fault, p.stanby_fault, p.disscrm, p.b_only,
		    p.dc_connected, p.max_port_speed, p.lpp, p.cable_speed,
		    p.connection_unreliable, p.beta_mode,
		    p.port_error,
		    p.loop_disable, p.in_standby, p.hard_disable
		);
	}
	printf("\n=== page 1 ===\n");
	read_phy_page(fd, (u_int8_t *)&v, 1, 0);
	printf(
	    "Compliance:%d\n"
	    "Vendor_ID:0x%06x\n"
	    "Product_ID:0x%06x\n",
	    v.compliance,
	    (v.vendor_id[0] << 16) | (v.vendor_id[1] << 8) | v.vendor_id[2],
	    (v.product_id[0] << 16) | (v.product_id[1] << 8) | v.product_id[2]
	);
}