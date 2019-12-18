#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int8_t ;
struct TYPE_5__ {scalar_t__ rmp_flnmsize; int /*<<< orphan*/  rmp_flnm; int /*<<< orphan*/  rmp_version; scalar_t__ rmp_session; int /*<<< orphan*/  rmp_seqno; int /*<<< orphan*/  rmp_retcode; int /*<<< orphan*/  rmp_type; } ;
struct rmp_packet {TYPE_1__ r_brpl; } ;
struct TYPE_6__ {int /*<<< orphan*/  rmplen; struct rmp_packet rmp; } ;
typedef  TYPE_2__ RMPCONN ;

/* Variables and functions */
 char* MyHost ; 
 int /*<<< orphan*/  RMPBOOTSIZE (scalar_t__) ; 
 int /*<<< orphan*/  RMP_BOOT_REPL ; 
 int /*<<< orphan*/  RMP_E_OKAY ; 
 scalar_t__ RMP_HOSTLEN ; 
 int /*<<< orphan*/  RMP_VERSION ; 
 int SendPacket (TYPE_2__*) ; 
 int /*<<< orphan*/  ZEROWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

int
SendServerID(RMPCONN *rconn)
{
	struct rmp_packet *rpl;
	char *src, *dst;
	u_int8_t *size;

	rpl = &rconn->rmp;			/* cache ptr to RMP packet */

	/*
	 *  Set up assorted fields in reply packet.
	 */
	rpl->r_brpl.rmp_type = RMP_BOOT_REPL;
	rpl->r_brpl.rmp_retcode = RMP_E_OKAY;
	ZEROWORD(rpl->r_brpl.rmp_seqno);
	rpl->r_brpl.rmp_session = 0;
	rpl->r_brpl.rmp_version = htons(RMP_VERSION);

	size = &rpl->r_brpl.rmp_flnmsize;	/* ptr to length of host name */

	/*
	 *  Copy our host name into the reply packet incrementing the
	 *  length as we go.  Stop at RMP_HOSTLEN or the first dot.
	 */
	src = MyHost;
	dst = (char *) &rpl->r_brpl.rmp_flnm;
	for (*size = 0; *size < RMP_HOSTLEN; (*size)++) {
		if (*src == '.' || *src == '\0')
			break;
		*dst++ = *src++;
	}

	rconn->rmplen = RMPBOOTSIZE(*size);	/* set packet length */

	return(SendPacket(rconn));		/* send packet */
}