#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  sha256; int /*<<< orphan*/  sha1; } ;
typedef  TYPE_1__ sctp_hash_context_t ;

/* Variables and functions */
#define  SCTP_AUTH_HMAC_ID_RSVD 130 
#define  SCTP_AUTH_HMAC_ID_SHA1 129 
#define  SCTP_AUTH_HMAC_ID_SHA256 128 
 int /*<<< orphan*/  SCTP_SHA1_UPDATE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_SHA256_UPDATE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sctp_hmac_update(uint16_t hmac_algo, sctp_hash_context_t *ctx,
    uint8_t *text, uint32_t textlen)
{
	switch (hmac_algo) {
	case SCTP_AUTH_HMAC_ID_SHA1:
		SCTP_SHA1_UPDATE(&ctx->sha1, text, textlen);
		break;
	case SCTP_AUTH_HMAC_ID_SHA256:
		SCTP_SHA256_UPDATE(&ctx->sha256, text, textlen);
		break;
	case SCTP_AUTH_HMAC_ID_RSVD:
	default:
		/* unknown HMAC algorithm: can't do anything */
		return;
	}			/* end switch */
}