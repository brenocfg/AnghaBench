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
typedef  size_t u_int ;
struct sshbuf {int dummy; } ;

/* Variables and functions */
 size_t KEX_COOKIE_LEN ; 
 size_t PROPOSAL_MAX ; 
 int sshbuf_put_cstring (struct sshbuf*,char*) ; 
 int sshbuf_put_u32 (struct sshbuf*,int /*<<< orphan*/ ) ; 
 int sshbuf_put_u8 (struct sshbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshbuf_reset (struct sshbuf*) ; 

int
kex_prop2buf(struct sshbuf *b, char *proposal[PROPOSAL_MAX])
{
	u_int i;
	int r;

	sshbuf_reset(b);

	/*
	 * add a dummy cookie, the cookie will be overwritten by
	 * kex_send_kexinit(), each time a kexinit is set
	 */
	for (i = 0; i < KEX_COOKIE_LEN; i++) {
		if ((r = sshbuf_put_u8(b, 0)) != 0)
			return r;
	}
	for (i = 0; i < PROPOSAL_MAX; i++) {
		if ((r = sshbuf_put_cstring(b, proposal[i])) != 0)
			return r;
	}
	if ((r = sshbuf_put_u8(b, 0)) != 0 ||	/* first_kex_packet_follows */
	    (r = sshbuf_put_u32(b, 0)) != 0)	/* uint32 reserved */
		return r;
	return 0;
}