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
typedef  int /*<<< orphan*/  u_char ;
struct tcphdr {int dummy; } ;
struct secasvar {int dummy; } ;
struct secasindex {scalar_t__ reqid; int /*<<< orphan*/  mode; int /*<<< orphan*/  proto; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IPSEC_MODE_TCPMD5 ; 
 int /*<<< orphan*/  KMOD_TCPSTAT_INC (int /*<<< orphan*/ ) ; 
 int TCP_SIGLEN ; 
 scalar_t__ bcmp (int /*<<< orphan*/ *,char*,int) ; 
 struct secasvar* key_allocsa_tcpmd5 (struct secasindex*) ; 
 int /*<<< orphan*/  key_freesav (struct secasvar**) ; 
 int /*<<< orphan*/  setsockaddrs (struct mbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_fields_to_host (struct tcphdr*) ; 
 int /*<<< orphan*/  tcp_fields_to_net (struct tcphdr*) ; 
 int /*<<< orphan*/  tcp_signature_compute (struct mbuf*,struct tcphdr*,struct secasvar*,char*) ; 
 int /*<<< orphan*/  tcps_sig_err_buildsig ; 
 int /*<<< orphan*/  tcps_sig_rcvbadsig ; 
 int /*<<< orphan*/  tcps_sig_rcvgoodsig ; 

__attribute__((used)) static int
tcp_ipsec_input(struct mbuf *m, struct tcphdr *th, u_char *buf)
{
	char tmpdigest[TCP_SIGLEN];
	struct secasindex saidx;
	struct secasvar *sav;

	setsockaddrs(m, &saidx.src, &saidx.dst);
	saidx.proto = IPPROTO_TCP;
	saidx.mode = IPSEC_MODE_TCPMD5;
	saidx.reqid = 0;
	sav = key_allocsa_tcpmd5(&saidx);
	if (sav == NULL) {
		KMOD_TCPSTAT_INC(tcps_sig_err_buildsig);
		return (EACCES);
	}
	/*
	 * tcp_input() operates with TCP header fields in host
	 * byte order. We expect them in network byte order.
	 */
	tcp_fields_to_net(th);
	tcp_signature_compute(m, th, sav, tmpdigest);
	tcp_fields_to_host(th);
	key_freesav(&sav);
	if (bcmp(buf, tmpdigest, TCP_SIGLEN) != 0) {
		KMOD_TCPSTAT_INC(tcps_sig_rcvbadsig);
		return (EACCES);
	}
	KMOD_TCPSTAT_INC(tcps_sig_rcvgoodsig);
	return (0);
}