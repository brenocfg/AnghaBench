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
typedef  size_t uint8_t ;
struct TYPE_3__ {int* chunks; int /*<<< orphan*/  num_chunks; } ;
typedef  TYPE_1__ sctp_auth_chklist_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 size_t SCTP_AUTHENTICATION ; 
 int /*<<< orphan*/  SCTP_DEBUG_AUTH1 ; 
 size_t SCTP_INITIATION ; 
 size_t SCTP_INITIATION_ACK ; 
 size_t SCTP_SHUTDOWN_COMPLETE ; 

int
sctp_auth_add_chunk(uint8_t chunk, sctp_auth_chklist_t *list)
{
	if (list == NULL)
		return (-1);

	/* is chunk restricted? */
	if ((chunk == SCTP_INITIATION) ||
	    (chunk == SCTP_INITIATION_ACK) ||
	    (chunk == SCTP_SHUTDOWN_COMPLETE) ||
	    (chunk == SCTP_AUTHENTICATION)) {
		return (-1);
	}
	if (list->chunks[chunk] == 0) {
		list->chunks[chunk] = 1;
		list->num_chunks++;
		SCTPDBG(SCTP_DEBUG_AUTH1,
		    "SCTP: added chunk %u (0x%02x) to Auth list\n",
		    chunk, chunk);
	}
	return (0);
}