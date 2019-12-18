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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 void* EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ERRS (char*,int,...) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IBWARN (char*,...) ; 
 scalar_t__ IB_MAD_SIZE ; 
 int /*<<< orphan*/  IB_MAD_TRID_F ; 
 int errno ; 
 int ibdebug ; 
 scalar_t__ mad_get_field64 (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,int) ; 
 scalar_t__ save_mad ; 
 int save_mad_len ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  umad_addr_dump (int /*<<< orphan*/ ) ; 
 void* umad_get_mad (void*) ; 
 int /*<<< orphan*/  umad_get_mad_addr (void*) ; 
 scalar_t__ umad_recv (int,void*,int*,int) ; 
 scalar_t__ umad_send (int,int,void*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ umad_size () ; 
 int umad_status (void*) ; 
 int /*<<< orphan*/  xdump (int /*<<< orphan*/ ,char*,void*,scalar_t__) ; 

__attribute__((used)) static int
_do_madrpc(int port_id, void *sndbuf, void *rcvbuf, int agentid, int len,
	   int timeout, int max_retries, int *p_error)
{
	uint32_t trid;		/* only low 32 bits - see mad_trid() */
	int retries;
	int length, status;

	if (ibdebug > 1) {
		IBWARN(">>> sending: len %d pktsz %zu", len, umad_size() + len);
		xdump(stderr, "send buf\n", sndbuf, umad_size() + len);
	}

	if (save_mad) {
		memcpy(save_mad, umad_get_mad(sndbuf),
		       save_mad_len < len ? save_mad_len : len);
		save_mad = 0;
	}

	if (max_retries <= 0) {
		errno = EINVAL;
		*p_error = EINVAL;
		ERRS("max_retries %d <= 0", max_retries);
		return -1;
	}

	trid =
	    (uint32_t) mad_get_field64(umad_get_mad(sndbuf), 0, IB_MAD_TRID_F);

	for (retries = 0; retries < max_retries; retries++) {
		if (retries)
			ERRS("retry %d (timeout %d ms)", retries, timeout);

		length = len;
		if (umad_send(port_id, agentid, sndbuf, length, timeout, 0) < 0) {
			IBWARN("send failed; %s", strerror(errno));
			return -1;
		}

		/* Use same timeout on receive side just in case */
		/* send packet is lost somewhere. */
		do {
			length = len;
			if (umad_recv(port_id, rcvbuf, &length, timeout) < 0) {
				IBWARN("recv failed: %s", strerror(errno));
				return -1;
			}

			if (ibdebug > 2)
				umad_addr_dump(umad_get_mad_addr(rcvbuf));
			if (ibdebug > 1) {
				IBWARN("rcv buf:");
				xdump(stderr, "rcv buf\n", umad_get_mad(rcvbuf),
				      IB_MAD_SIZE);
			}
		} while ((uint32_t)
			 mad_get_field64(umad_get_mad(rcvbuf), 0,
					 IB_MAD_TRID_F) != trid);

		status = umad_status(rcvbuf);
		if (!status)
			return length;	/* done */
		if (status == ENOMEM)
			return length;
	}

	errno = status;
	*p_error = ETIMEDOUT;
	ERRS("timeout after %d retries, %d ms", retries, timeout * retries);
	return -1;
}