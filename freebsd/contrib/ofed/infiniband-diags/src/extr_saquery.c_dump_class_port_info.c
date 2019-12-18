#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int base_ver; int class_ver; int /*<<< orphan*/  trap_qkey; int /*<<< orphan*/  trap_hop_qp; int /*<<< orphan*/  trap_pkey; int /*<<< orphan*/  trap_lid; int /*<<< orphan*/  trap_tc_sl_fl; int /*<<< orphan*/  trap_gid; int /*<<< orphan*/  redir_qkey; int /*<<< orphan*/  redir_qp; int /*<<< orphan*/  redir_pkey; int /*<<< orphan*/  redir_lid; int /*<<< orphan*/  redir_tc_sl_fl; int /*<<< orphan*/  redir_gid; int /*<<< orphan*/  cap_mask; } ;
typedef  TYPE_1__ ib_class_port_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int INET6_ADDRSTRLEN ; 
 int cl_ntoh16 (int /*<<< orphan*/ ) ; 
 int cl_ntoh32 (int /*<<< orphan*/ ) ; 
 int ib_class_cap_mask2 (TYPE_1__*) ; 
 int ib_class_resp_time_val (TYPE_1__*) ; 
 char* inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,char*,int,int,int,int,int,char*,int,int,int,int,int) ; 

__attribute__((used)) static void dump_class_port_info(ib_class_port_info_t *cpi)
{
	char gid_str[INET6_ADDRSTRLEN];
	char gid_str2[INET6_ADDRSTRLEN];

	printf("SA ClassPortInfo:\n"
	       "\t\tBase version.............%d\n"
	       "\t\tClass version............%d\n"
	       "\t\tCapability mask..........0x%04X\n"
	       "\t\tCapability mask 2........0x%08X\n"
	       "\t\tResponse time value......0x%02X\n"
	       "\t\tRedirect GID.............%s\n"
	       "\t\tRedirect TC/SL/FL........0x%08X\n"
	       "\t\tRedirect LID.............%u\n"
	       "\t\tRedirect PKey............0x%04X\n"
	       "\t\tRedirect QP..............0x%08X\n"
	       "\t\tRedirect QKey............0x%08X\n"
	       "\t\tTrap GID.................%s\n"
	       "\t\tTrap TC/SL/FL............0x%08X\n"
	       "\t\tTrap LID.................%u\n"
	       "\t\tTrap PKey................0x%04X\n"
	       "\t\tTrap HL/QP...............0x%08X\n"
	       "\t\tTrap QKey................0x%08X\n",
	       cpi->base_ver, cpi->class_ver, cl_ntoh16(cpi->cap_mask),
	       ib_class_cap_mask2(cpi), ib_class_resp_time_val(cpi),
	       inet_ntop(AF_INET6, &(cpi->redir_gid), gid_str, sizeof gid_str),
	       cl_ntoh32(cpi->redir_tc_sl_fl), cl_ntoh16(cpi->redir_lid),
	       cl_ntoh16(cpi->redir_pkey), cl_ntoh32(cpi->redir_qp),
	       cl_ntoh32(cpi->redir_qkey),
	       inet_ntop(AF_INET6, &(cpi->trap_gid), gid_str2, sizeof gid_str2),
	       cl_ntoh32(cpi->trap_tc_sl_fl), cl_ntoh16(cpi->trap_lid),
	       cl_ntoh16(cpi->trap_pkey), cl_ntoh32(cpi->trap_hop_qp),
	       cl_ntoh32(cpi->trap_qkey));
}