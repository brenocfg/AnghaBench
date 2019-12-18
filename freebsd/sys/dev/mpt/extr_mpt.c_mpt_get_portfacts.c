#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mpt_softc {int dummy; } ;
typedef  int /*<<< orphan*/  U8 ;
struct TYPE_4__ {int /*<<< orphan*/  MsgContext; int /*<<< orphan*/  PortNumber; int /*<<< orphan*/  Function; } ;
typedef  int /*<<< orphan*/  MSG_PORT_FACTS_REPLY ;
typedef  TYPE_1__ MSG_PORT_FACTS ;

/* Variables and functions */
 int /*<<< orphan*/  MPI_FUNCTION_PORT_FACTS ; 
 int /*<<< orphan*/  MPT_REPLY_HANDLER_HANDSHAKE ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int mpt_recv_handshake_reply (struct mpt_softc*,int,int /*<<< orphan*/ *) ; 
 int mpt_send_handshake_cmd (struct mpt_softc*,int,TYPE_1__*) ; 

__attribute__((used)) static int
mpt_get_portfacts(struct mpt_softc *mpt, U8 port, MSG_PORT_FACTS_REPLY *freplp)
{
	MSG_PORT_FACTS f_req;
	int error;
	
	memset(&f_req, 0, sizeof f_req);
	f_req.Function = MPI_FUNCTION_PORT_FACTS;
	f_req.PortNumber = port;
	f_req.MsgContext = htole32(MPT_REPLY_HANDLER_HANDSHAKE);
	error = mpt_send_handshake_cmd(mpt, sizeof f_req, &f_req);
	if (error) {
		return(error);
	}
	error = mpt_recv_handshake_reply(mpt, sizeof (*freplp), freplp);
	return (error);
}