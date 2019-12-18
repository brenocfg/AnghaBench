#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  TYPE_1__* res_state ;
typedef  int /*<<< orphan*/  ns_msg ;
struct TYPE_4__ {int pfcode; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  RES_PRF_ADD ; 
 int /*<<< orphan*/  RES_PRF_ANS ; 
 int /*<<< orphan*/  RES_PRF_AUTH ; 
 int RES_PRF_HEAD1 ; 
 int RES_PRF_HEAD2 ; 
 int RES_PRF_HEADX ; 
 int /*<<< orphan*/  RES_PRF_QUES ; 
 char** _res_opcodes ; 
 int /*<<< orphan*/  do_section (TYPE_1__* const,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  ns_f_aa ; 
 int /*<<< orphan*/  ns_f_ad ; 
 int /*<<< orphan*/  ns_f_cd ; 
 int /*<<< orphan*/  ns_f_opcode ; 
 int /*<<< orphan*/  ns_f_qr ; 
 int /*<<< orphan*/  ns_f_ra ; 
 int /*<<< orphan*/  ns_f_rcode ; 
 int /*<<< orphan*/  ns_f_rd ; 
 int /*<<< orphan*/  ns_f_tc ; 
 int /*<<< orphan*/  ns_f_z ; 
 scalar_t__ ns_initparse (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int ns_msg_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ns_msg_getflag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ns_msg_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_s_an ; 
 int /*<<< orphan*/  ns_s_ar ; 
 int /*<<< orphan*/  ns_s_ns ; 
 int /*<<< orphan*/  ns_s_qd ; 
 char* p_rcode (size_t) ; 
 char* p_section (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

void
res_pquery(const res_state statp, const u_char *msg, int len, FILE *file) {
	ns_msg handle;
	int qdcount, ancount, nscount, arcount;
	u_int opcode, rcode, id;

	if (ns_initparse(msg, len, &handle) < 0) {
		fprintf(file, ";; ns_initparse: %s\n", strerror(errno));
		return;
	}
	opcode = ns_msg_getflag(handle, ns_f_opcode);
	rcode = ns_msg_getflag(handle, ns_f_rcode);
	id = ns_msg_id(handle);
	qdcount = ns_msg_count(handle, ns_s_qd);
	ancount = ns_msg_count(handle, ns_s_an);
	nscount = ns_msg_count(handle, ns_s_ns);
	arcount = ns_msg_count(handle, ns_s_ar);

	/*
	 * Print header fields.
	 */
	if ((!statp->pfcode) || (statp->pfcode & RES_PRF_HEADX) || rcode)
		fprintf(file,
			";; ->>HEADER<<- opcode: %s, status: %s, id: %d\n",
			_res_opcodes[opcode], p_rcode(rcode), id);
	if ((!statp->pfcode) || (statp->pfcode & RES_PRF_HEADX))
		putc(';', file);
	if ((!statp->pfcode) || (statp->pfcode & RES_PRF_HEAD2)) {
		fprintf(file, "; flags:");
		if (ns_msg_getflag(handle, ns_f_qr))
			fprintf(file, " qr");
		if (ns_msg_getflag(handle, ns_f_aa))
			fprintf(file, " aa");
		if (ns_msg_getflag(handle, ns_f_tc))
			fprintf(file, " tc");
		if (ns_msg_getflag(handle, ns_f_rd))
			fprintf(file, " rd");
		if (ns_msg_getflag(handle, ns_f_ra))
			fprintf(file, " ra");
		if (ns_msg_getflag(handle, ns_f_z))
			fprintf(file, " ??");
		if (ns_msg_getflag(handle, ns_f_ad))
			fprintf(file, " ad");
		if (ns_msg_getflag(handle, ns_f_cd))
			fprintf(file, " cd");
	}
	if ((!statp->pfcode) || (statp->pfcode & RES_PRF_HEAD1)) {
		fprintf(file, "; %s: %d",
			p_section(ns_s_qd, opcode), qdcount);
		fprintf(file, ", %s: %d",
			p_section(ns_s_an, opcode), ancount);
		fprintf(file, ", %s: %d",
			p_section(ns_s_ns, opcode), nscount);
		fprintf(file, ", %s: %d",
			p_section(ns_s_ar, opcode), arcount);
	}
	if ((!statp->pfcode) || (statp->pfcode &
		(RES_PRF_HEADX | RES_PRF_HEAD2 | RES_PRF_HEAD1))) {
		putc('\n',file);
	}
	/*
	 * Print the various sections.
	 */
	do_section(statp, &handle, ns_s_qd, RES_PRF_QUES, file);
	do_section(statp, &handle, ns_s_an, RES_PRF_ANS, file);
	do_section(statp, &handle, ns_s_ns, RES_PRF_AUTH, file);
	do_section(statp, &handle, ns_s_ar, RES_PRF_ADD, file);
	if (qdcount == 0 && ancount == 0 &&
	    nscount == 0 && arcount == 0)
		putc('\n', file);
}