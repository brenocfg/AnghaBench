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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_AUTH_DIGEST_LEN_SHA1 ; 
 int /*<<< orphan*/  SCTP_AUTH_DIGEST_LEN_SHA256 ; 
#define  SCTP_AUTH_HMAC_ID_SHA1 129 
#define  SCTP_AUTH_HMAC_ID_SHA256 128 

uint32_t
sctp_get_hmac_digest_len(uint16_t hmac_algo)
{
	switch (hmac_algo) {
	case SCTP_AUTH_HMAC_ID_SHA1:
		return (SCTP_AUTH_DIGEST_LEN_SHA1);
	case SCTP_AUTH_HMAC_ID_SHA256:
		return (SCTP_AUTH_DIGEST_LEN_SHA256);
	default:
		/* unknown HMAC algorithm: can't do anything */
		return (0);
	}			/* end switch */
}