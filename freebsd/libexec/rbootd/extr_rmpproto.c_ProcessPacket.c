#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  rmp_seqno; int /*<<< orphan*/  rmp_session; } ;
struct rmp_packet {int r_type; TYPE_1__ r_brq; } ;
struct TYPE_18__ {int /*<<< orphan*/  files; } ;
struct TYPE_17__ {struct rmp_packet rmp; } ;
typedef  TYPE_2__ RMPCONN ;
typedef  TYPE_3__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  AddConn (TYPE_2__*) ; 
 int /*<<< orphan*/  BootDone (TYPE_2__*) ; 
 int /*<<< orphan*/  BootFiles ; 
 int /*<<< orphan*/  EnetStr (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeConn (TYPE_2__*) ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 TYPE_2__* NewConn (TYPE_2__*) ; 
#define  RMP_BOOT_DONE 132 
#define  RMP_BOOT_REPL 131 
#define  RMP_BOOT_REQ 130 
 int /*<<< orphan*/  RMP_PROBESID ; 
#define  RMP_READ_REPL 129 
#define  RMP_READ_REQ 128 
 int /*<<< orphan*/  SendBootRepl (struct rmp_packet*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendFileNo (struct rmp_packet*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendReadRepl (TYPE_2__*) ; 
 int /*<<< orphan*/  SendServerID (TYPE_2__*) ; 
 int /*<<< orphan*/  WORDZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

void
ProcessPacket(RMPCONN *rconn, CLIENT *client)
{
	struct rmp_packet *rmp;
	RMPCONN *rconnout;

	rmp = &rconn->rmp;		/* cache pointer to RMP packet */

	switch(rmp->r_type) {		/* do what we came here to do */
		case RMP_BOOT_REQ:		/* boot request */
			if ((rconnout = NewConn(rconn)) == NULL)
				return;

			/*
			 *  If the Session ID is 0xffff, this is a "probe"
			 *  packet and we do not want to add the connection
			 *  to the linked list of active connections.  There
			 *  are two types of probe packets, if the Sequence
			 *  Number is 0 they want to know our host name, o/w
			 *  they want the name of the file associated with
			 *  the number spec'd by the Sequence Number.
			 *
			 *  If this is an actual boot request, open the file
			 *  and send a reply.  If SendBootRepl() does not
			 *  return 0, add the connection to the linked list
			 *  of active connections, otherwise delete it since
			 *  an error was encountered.
			 */
			if (ntohs(rmp->r_brq.rmp_session) == RMP_PROBESID) {
				if (WORDZE(rmp->r_brq.rmp_seqno))
					(void) SendServerID(rconnout);
				else
					(void) SendFileNo(rmp, rconnout,
					                  client? client->files:
					                          BootFiles);
				FreeConn(rconnout);
			} else {
				if (SendBootRepl(rmp, rconnout,
				    client? client->files: BootFiles))
					AddConn(rconnout);
				else
					FreeConn(rconnout);
			}
			break;

		case RMP_BOOT_REPL:		/* boot reply (not valid) */
			syslog(LOG_WARNING, "%s: sent a boot reply",
			       EnetStr(rconn));
			break;

		case RMP_READ_REQ:		/* read request */
			/*
			 *  Send a portion of the boot file.
			 */
			(void) SendReadRepl(rconn);
			break;

		case RMP_READ_REPL:		/* read reply (not valid) */
			syslog(LOG_WARNING, "%s: sent a read reply",
			       EnetStr(rconn));
			break;

		case RMP_BOOT_DONE:		/* boot complete */
			/*
			 *  Remove the entry from the linked list of active
			 *  connections.
			 */
			(void) BootDone(rconn);
			break;

		default:			/* unknown RMP packet type */
			syslog(LOG_WARNING, "%s: unknown packet type (%u)",
			       EnetStr(rconn), rmp->r_type);
	}
}