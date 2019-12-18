#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct mbuf {int dummy; } ;
struct cbcp_header {int /*<<< orphan*/  length; int /*<<< orphan*/  id; int /*<<< orphan*/  code; } ;
struct cbcp_data {scalar_t__ length; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct cbcp {TYPE_3__* p; TYPE_1__ fsm; } ;
struct TYPE_6__ {int /*<<< orphan*/  link; TYPE_2__* dl; } ;
struct TYPE_5__ {int /*<<< orphan*/  bundle; } ;

/* Variables and functions */
 scalar_t__ LINK_QUEUES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LogDEBUG ; 
 scalar_t__ MBUF_CTOP (struct mbuf*) ; 
 int /*<<< orphan*/  MB_CBCPOUT ; 
 int /*<<< orphan*/  PROTO_CBCP ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int /*<<< orphan*/  link_PushPacket (int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_DumpBp (int /*<<< orphan*/ ,char*,struct mbuf*) ; 
 struct mbuf* m_get (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct cbcp_data*,scalar_t__) ; 

__attribute__((used)) static void
cbcp_Output(struct cbcp *cbcp, u_char code, struct cbcp_data *data)
{
  struct cbcp_header *head;
  struct mbuf *bp;

  bp = m_get(sizeof *head + data->length, MB_CBCPOUT);
  head = (struct cbcp_header *)MBUF_CTOP(bp);
  head->code = code;
  head->id = cbcp->fsm.id;
  head->length = htons(sizeof *head + data->length);
  memcpy(MBUF_CTOP(bp) + sizeof *head, data, data->length);
  log_DumpBp(LogDEBUG, "cbcp_Output", bp);
  link_PushPacket(&cbcp->p->link, bp, cbcp->p->dl->bundle,
                  LINK_QUEUES(&cbcp->p->link) - 1, PROTO_CBCP);
}