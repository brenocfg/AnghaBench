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
struct adreq {int adr_cmd; char* adr_data; int /*<<< orphan*/  adr_datasize; } ;

/* Variables and functions */
#define  ADIST_CMD_CLOSE 129 
#define  ADIST_CMD_OPEN 128 
 int /*<<< orphan*/  EX_PROTOCOL ; 
 int /*<<< orphan*/  pjdlog_exitx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strchr (char*,char) ; 

__attribute__((used)) static void
adreq_validate_data(const struct adreq *adreq)
{

	/* Validate packet data. */

	switch (adreq->adr_cmd) {
	case ADIST_CMD_OPEN:
	case ADIST_CMD_CLOSE:
		/*
		 * File name must end up with '\0' and there must be no '\0'
		 * in the middle.
		 */
		if (adreq->adr_data[adreq->adr_datasize - 1] != '\0' ||
		    strchr(adreq->adr_data, '\0') !=
		    (const char *)adreq->adr_data + adreq->adr_datasize - 1) {
			pjdlog_exitx(EX_PROTOCOL,
			    "Invalid file name received.");
		}
		break;
	}
}