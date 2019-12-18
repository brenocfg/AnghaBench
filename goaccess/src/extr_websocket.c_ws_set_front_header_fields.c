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
struct TYPE_5__ {char* buf; int res; int /*<<< orphan*/  masking; int /*<<< orphan*/  opcode; int /*<<< orphan*/  fin; } ;
typedef  TYPE_1__ WSFrame ;
struct TYPE_6__ {TYPE_1__* frame; } ;
typedef  TYPE_2__ WSClient ;

/* Variables and functions */
 int WS_CLOSE ; 
 int WS_ERR ; 
 int /*<<< orphan*/  WS_FRM_FIN (char) ; 
 int /*<<< orphan*/  WS_FRM_MASK (char) ; 
 int /*<<< orphan*/  WS_FRM_OPCODE (char) ; 
 scalar_t__ WS_FRM_R1 (char) ; 
 scalar_t__ WS_FRM_R2 (char) ; 
 scalar_t__ WS_FRM_R3 (char) ; 
 int ws_set_status (TYPE_2__*,int,int) ; 

__attribute__((used)) static int
ws_set_front_header_fields (WSClient * client)
{
  WSFrame **frm = &client->frame;
  char *buf = (*frm)->buf;

  (*frm)->fin = WS_FRM_FIN (*(buf));
  (*frm)->masking = WS_FRM_MASK (*(buf + 1));
  (*frm)->opcode = WS_FRM_OPCODE (*(buf));
  (*frm)->res = WS_FRM_R1 (*(buf)) || WS_FRM_R2 (*(buf)) || WS_FRM_R3 (*(buf));

  /* should be masked and can't be using RESVd  bits */
  if (!(*frm)->masking || (*frm)->res)
    return ws_set_status (client, WS_ERR | WS_CLOSE, 1);

  return 0;
}