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
typedef  int uintmax_t ;
struct adreq {scalar_t__ adr_byteorder; scalar_t__ adr_datasize; int adr_cmd; int /*<<< orphan*/  adr_seq; } ;

/* Variables and functions */
 scalar_t__ ADIST_BUF_SIZE ; 
 scalar_t__ ADIST_BYTEORDER ; 
#define  ADIST_CMD_APPEND 132 
#define  ADIST_CMD_CLOSE 131 
#define  ADIST_CMD_ERROR 130 
#define  ADIST_CMD_KEEPALIVE 129 
#define  ADIST_CMD_OPEN 128 
 int /*<<< orphan*/  EX_PROTOCOL ; 
 scalar_t__ bswap32 (scalar_t__) ; 
 int /*<<< orphan*/  bswap64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pjdlog_exitx (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
adreq_decode_and_validate_header(struct adreq *adreq)
{

	/* Byte-swap only if the sender is using different byte order. */
	if (adreq->adr_byteorder != ADIST_BYTEORDER) {
		adreq->adr_byteorder = ADIST_BYTEORDER;
		adreq->adr_seq = bswap64(adreq->adr_seq);
		adreq->adr_datasize = bswap32(adreq->adr_datasize);
	}

	/* Validate packet header. */

	if (adreq->adr_datasize > ADIST_BUF_SIZE) {
		pjdlog_exitx(EX_PROTOCOL, "Invalid datasize received (%ju).",
		    (uintmax_t)adreq->adr_datasize);
	}

	switch (adreq->adr_cmd) {
	case ADIST_CMD_OPEN:
	case ADIST_CMD_APPEND:
	case ADIST_CMD_CLOSE:
		if (adreq->adr_datasize == 0) {
			pjdlog_exitx(EX_PROTOCOL,
			    "Invalid datasize received (%ju).",
			    (uintmax_t)adreq->adr_datasize);
		}
		break;
	case ADIST_CMD_KEEPALIVE:
	case ADIST_CMD_ERROR:
		if (adreq->adr_datasize > 0) {
			pjdlog_exitx(EX_PROTOCOL,
			    "Invalid datasize received (%ju).",
			    (uintmax_t)adreq->adr_datasize);
		}
		break;
	default:
		pjdlog_exitx(EX_PROTOCOL, "Invalid command received (%hhu).",
		    adreq->adr_cmd);
	}
}