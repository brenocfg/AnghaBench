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
struct timeval {int dummy; } ;
struct pkt {int ppoll; int /*<<< orphan*/ * exten; int /*<<< orphan*/  stratum; int /*<<< orphan*/  xmt; } ;
struct key {int dummy; } ;
typedef  int /*<<< orphan*/  l_fp ;

/* Variables and functions */
 int /*<<< orphan*/  HTONL_FP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ KEY_MAC_LEN ; 
 int /*<<< orphan*/  LEAP_NOTINSYNC ; 
 int LEN_PKT_NOMAC ; 
 int /*<<< orphan*/  MAX_MDG_LEN ; 
 int /*<<< orphan*/  STRATUM_TO_PKT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRATUM_UNSPEC ; 
 int /*<<< orphan*/  TVTOTS (struct timeval const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZERO (struct pkt) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  htonl (int) ; 
 int make_mac (struct pkt*,int,int /*<<< orphan*/ ,struct key*,char*) ; 
 int /*<<< orphan*/  ntpver ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  set_li_vn_mode (struct pkt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
generate_pkt (
	struct pkt *x_pkt,
	const struct timeval *tv_xmt,
	int key_id,
	struct key *pkt_key
	)
{
	l_fp	xmt_fp;
	int	pkt_len;
	int	mac_size;

	pkt_len = LEN_PKT_NOMAC;
	ZERO(*x_pkt);
	TVTOTS(tv_xmt, &xmt_fp);
	HTONL_FP(&xmt_fp, &x_pkt->xmt);
	x_pkt->stratum = STRATUM_TO_PKT(STRATUM_UNSPEC);
	x_pkt->ppoll = 8;
	/* FIXME! Modus broadcast + adr. check -> bdr. pkt */
	set_li_vn_mode(x_pkt, LEAP_NOTINSYNC, ntpver, 3);
	if (debug > 0) {
		printf("generate_pkt: key_id %d, key pointer %p\n", key_id, pkt_key);
	}
	if (pkt_key != NULL) {
		x_pkt->exten[0] = htonl(key_id);
		mac_size = make_mac(x_pkt, pkt_len, MAX_MDG_LEN,
				    pkt_key, (char *)&x_pkt->exten[1]);
		if (mac_size > 0)
			pkt_len += mac_size + KEY_MAC_LEN;
#ifdef DEBUG
		if (debug > 0) {
			printf("generate_pkt: mac_size is %d\n", mac_size);
		}
#endif

	}
	return pkt_len;
}