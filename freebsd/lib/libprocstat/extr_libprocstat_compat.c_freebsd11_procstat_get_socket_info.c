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
struct sockstat {int /*<<< orphan*/  dname; int /*<<< orphan*/  type; int /*<<< orphan*/  sa_peer; int /*<<< orphan*/  sa_local; int /*<<< orphan*/  so_snd_sb_state; int /*<<< orphan*/  so_rcv_sb_state; int /*<<< orphan*/  proto; int /*<<< orphan*/  dom_family; int /*<<< orphan*/  unp_conn; int /*<<< orphan*/  so_pcb; int /*<<< orphan*/  so_addr; int /*<<< orphan*/  inp_ppcb; } ;
struct procstat {int dummy; } ;
struct freebsd11_sockstat {int /*<<< orphan*/  dname; int /*<<< orphan*/  type; int /*<<< orphan*/  sa_peer; int /*<<< orphan*/  sa_local; int /*<<< orphan*/  so_snd_sb_state; int /*<<< orphan*/  so_rcv_sb_state; int /*<<< orphan*/  proto; int /*<<< orphan*/  dom_family; int /*<<< orphan*/  unp_conn; int /*<<< orphan*/  so_pcb; int /*<<< orphan*/  so_addr; int /*<<< orphan*/  inp_ppcb; } ;
struct filestat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int procstat_get_socket_info (struct procstat*,struct filestat*,struct sockstat*,char*) ; 

int
freebsd11_procstat_get_socket_info(struct procstat *procstat, struct filestat *fst,
    struct freebsd11_sockstat *sock_compat, char *errbuf)
{
	struct sockstat sock;
	int r;

	r = procstat_get_socket_info(procstat, fst, &sock, errbuf);
	if (r != 0)
		return (r);
	sock_compat->inp_ppcb = sock.inp_ppcb;
	sock_compat->so_addr = sock.so_addr;
	sock_compat->so_pcb = sock.so_pcb;
	sock_compat->unp_conn = sock.unp_conn;
	sock_compat->dom_family = sock.dom_family;
	sock_compat->proto = sock.proto;
	sock_compat->so_rcv_sb_state = sock.so_rcv_sb_state;
	sock_compat->so_snd_sb_state = sock.so_snd_sb_state;
	sock_compat->sa_local = sock.sa_local;
	sock_compat->sa_peer = sock.sa_peer;
	sock_compat->type = sock.type;
	memcpy(sock_compat->dname, sock.dname, sizeof(sock.dname));
	return (0);
}