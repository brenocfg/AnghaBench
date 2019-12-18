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
 struct secasvar* key_allocsa_tcpmd5 (struct secasindex*) ; 
 int /*<<< orphan*/  key_freesav (struct secasvar**) ; 
 int /*<<< orphan*/  setsockaddrs (struct mbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_signature_compute (struct mbuf*,struct tcphdr*,struct secasvar*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcps_sig_err_buildsig ; 

__attribute__((used)) static int
tcp_ipsec_output(struct mbuf *m, struct tcphdr *th, u_char *buf)
{
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
	tcp_signature_compute(m, th, sav, buf);
	key_freesav(&sav);
	return (0);
}