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
typedef  int uint16_t ;

/* Variables and functions */
#define  SCTP_AUTH_HMAC_ID_RSVD 130 
#define  SCTP_AUTH_HMAC_ID_SHA1 129 
#define  SCTP_AUTH_HMAC_ID_SHA256 128 

__attribute__((used)) static inline int
sctp_get_hmac_block_len(uint16_t hmac_algo)
{
	switch (hmac_algo) {
	case SCTP_AUTH_HMAC_ID_SHA1:
		return (64);
	case SCTP_AUTH_HMAC_ID_SHA256:
		return (64);
	case SCTP_AUTH_HMAC_ID_RSVD:
	default:
		/* unknown HMAC algorithm: can't do anything */
		return (0);
	}			/* end switch */
}