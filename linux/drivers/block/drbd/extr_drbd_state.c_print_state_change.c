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
union drbd_state {scalar_t__ role; scalar_t__ peer; scalar_t__ conn; scalar_t__ disk; scalar_t__ pdsk; } ;
typedef  enum chg_state_flags { ____Placeholder_chg_state_flags } chg_state_flags ;

/* Variables and functions */
 int CS_DC_CONN ; 
 int CS_DC_DISK ; 
 int CS_DC_PDSK ; 
 int CS_DC_PEER ; 
 int CS_DC_ROLE ; 
 char* drbd_conn_str (scalar_t__) ; 
 char* drbd_disk_str (scalar_t__) ; 
 char* drbd_role_str (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 

__attribute__((used)) static long print_state_change(char *pb, union drbd_state os, union drbd_state ns,
			       enum chg_state_flags flags)
{
	char *pbp;
	pbp = pb;
	*pbp = 0;

	if (ns.role != os.role && flags & CS_DC_ROLE)
		pbp += sprintf(pbp, "role( %s -> %s ) ",
			       drbd_role_str(os.role),
			       drbd_role_str(ns.role));
	if (ns.peer != os.peer && flags & CS_DC_PEER)
		pbp += sprintf(pbp, "peer( %s -> %s ) ",
			       drbd_role_str(os.peer),
			       drbd_role_str(ns.peer));
	if (ns.conn != os.conn && flags & CS_DC_CONN)
		pbp += sprintf(pbp, "conn( %s -> %s ) ",
			       drbd_conn_str(os.conn),
			       drbd_conn_str(ns.conn));
	if (ns.disk != os.disk && flags & CS_DC_DISK)
		pbp += sprintf(pbp, "disk( %s -> %s ) ",
			       drbd_disk_str(os.disk),
			       drbd_disk_str(ns.disk));
	if (ns.pdsk != os.pdsk && flags & CS_DC_PDSK)
		pbp += sprintf(pbp, "pdsk( %s -> %s ) ",
			       drbd_disk_str(os.pdsk),
			       drbd_disk_str(ns.pdsk));

	return pbp - pb;
}