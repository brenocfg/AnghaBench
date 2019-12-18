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
struct TYPE_5__ {scalar_t__ rmp_flnmsize; int /*<<< orphan*/  rmp_retcode; int /*<<< orphan*/  rmp_flnm; int /*<<< orphan*/  rmp_version; scalar_t__ rmp_session; int /*<<< orphan*/  rmp_seqno; int /*<<< orphan*/  rmp_type; } ;
struct rmp_packet {TYPE_1__ r_brpl; } ;
struct TYPE_6__ {int /*<<< orphan*/  rmplen; struct rmp_packet rmp; } ;
typedef  TYPE_2__ RMPCONN ;

/* Variables and functions */
 int C_MAXFILE ; 
 int /*<<< orphan*/  GETWORD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PUTWORD (int,int /*<<< orphan*/ ) ; 
 scalar_t__ RMPBOOTDATA ; 
 int /*<<< orphan*/  RMPBOOTSIZE (scalar_t__) ; 
 int /*<<< orphan*/  RMP_BOOT_REPL ; 
 int /*<<< orphan*/  RMP_E_NODFLT ; 
 int /*<<< orphan*/  RMP_E_OKAY ; 
 int /*<<< orphan*/  RMP_VERSION ; 
 int SendPacket (TYPE_2__*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

int
SendFileNo(struct rmp_packet *req, RMPCONN *rconn, char *filelist[])
{
	struct rmp_packet *rpl;
	char *src, *dst;
	u_int8_t *size;
	int i;

	GETWORD(req->r_brpl.rmp_seqno, i);	/* SeqNo is really FileNo */
	rpl = &rconn->rmp;			/* cache ptr to RMP packet */

	/*
	 *  Set up assorted fields in reply packet.
	 */
	rpl->r_brpl.rmp_type = RMP_BOOT_REPL;
	PUTWORD(i, rpl->r_brpl.rmp_seqno);
	i--;
	rpl->r_brpl.rmp_session = 0;
	rpl->r_brpl.rmp_version = htons(RMP_VERSION);

	size = &rpl->r_brpl.rmp_flnmsize;	/* ptr to length of filename */
	*size = 0;				/* init length to zero */

	/*
	 *  Copy the file name into the reply packet incrementing the
	 *  length as we go.  Stop at end of string or when RMPBOOTDATA
	 *  characters have been copied.  Also, set return code to
	 *  indicate success or "no more files".
	 */
	if (i < C_MAXFILE && filelist[i] != NULL) {
		src = filelist[i];
		dst = (char *)&rpl->r_brpl.rmp_flnm;
		for (; *src && *size < RMPBOOTDATA; (*size)++) {
			if (*src == '\0')
				break;
			*dst++ = *src++;
		}
		rpl->r_brpl.rmp_retcode = RMP_E_OKAY;
	} else
		rpl->r_brpl.rmp_retcode = RMP_E_NODFLT;

	rconn->rmplen = RMPBOOTSIZE(*size);	/* set packet length */

	return(SendPacket(rconn));		/* send packet */
}